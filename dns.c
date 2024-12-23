#include "dns.h"
// Convert a DNS format name to dot format
// For example, "\x03www\x07example\x03com\x00" becomes "www.example.com"
// The output buffer must be large enough to hold the converted name

size_t countNameLength(const char *name) {
    int i = 0;
    while (name[i] != '\0') {
        i += (name[i] + 1);
    }
    return i + 1;
}
DNSMessage parseDNSMessage(uint8_t *datagram, uint8_t **end) {
    DNSMessage message;
    // 解析 header
    message.header = (DNSHeader *) datagram;
    uint8_t *ptr = datagram + DNS_HEADER_OFFSET;
    // 解析 question
    uint16_t questionCount = ntohs(message.header->qdcount);
    message.questions = malloc(questionCount * sizeof(Question));
    for (int i = 0; i < questionCount; i ++) {
        message.questions[i].QNAME = ptr;
        size_t length = countNameLength((const char *) ptr);
        ptr += length;
        message.questions[i].QTYPE = *((uint16_t *) (ptr));
        ptr += sizeof(uint16_t);
        message.questions[i].QCLASS = *((uint16_t *) (ptr));
        ptr += sizeof(uint16_t);
    }
    uint16_t answerCount = ntohs(message.header->ancount);
    parseResourceRecordFields(&ptr, &message.answers, answerCount);
    uint16_t authorityCount = ntohs(message.header->nscount);
    parseResourceRecordFields(&ptr, &message.authorities, authorityCount);
    uint16_t additionalCount = ntohs(message.header->arcount);
    parseResourceRecordFields(&ptr, &message.additionalRecords, additionalCount);
    *end = ptr;
    return message;
}
void parseResourceRecord(uint8_t **begin, ResourceRecord *rr) {
    rr->NAME = *begin;
    size_t length;
    if ((*(rr->NAME) & 0xc0) == 0xc0) {
        length = 2;
    } else {
        length = countNameLength((const char *) *begin);
    }
    *begin += length;
    rr->TYPE = ntohs(*((uint16_t *) *begin));
    *begin += sizeof(uint16_t);
    rr->CLASS = ntohs(*((uint16_t *) *begin));
    *begin += sizeof(uint16_t);
    rr->TTL = ntohl(*((uint32_t *) *begin));
    *begin += sizeof(uint32_t);
    rr->RDLENGTH = ntohs(*((uint16_t *) *begin));
    *begin += sizeof(uint16_t);
    rr->RDATA = *begin;
    *begin += rr->RDLENGTH;
}

void parseResourceRecordFields(uint8_t **ptr, ResourceRecord **records, uint16_t count) {
    if (count > 0) {
        *records = malloc(count * sizeof(ResourceRecord));
        for (int i = 0; i < count; i ++) {
            parseResourceRecord(ptr, &(*records)[i]);
        }
    } else {
        *records = NULL;
    }
}
void cacheEntry(ResourceRecord *rrs, uint16_t count, uint8_t *start) {
    for (int i = 0; i < count; i ++) {
        ResourceRecord *answer = rrs + i;
        if (answer->CLASS == 1 && (answer->TYPE == 1 || answer->TYPE == 28)) {
            uint8_t *domain = malloc(sizeof(char) * MAX_DOMAIN_LENGTH);
            uint8_t judge = 0xc0;
            uint8_t test = *((uint8_t *) answer->NAME);
            if ((test & judge) == judge) {
                /*uint16_t offset = htons((uint16_t *) answer->NAME);
                offset &= 0x3fff;*/
                uint8_t *ptr = start + 12;
                memcpy(domain, ptr, strlen((char *) ptr) + 1);
            } else {
                memcpy(domain, answer->NAME, (strlen((char *) answer->NAME) + 1) * sizeof(uint8_t));
            }
            if (answer->TYPE == 1) {
                uint32_t ip = *((uint32_t *) answer->RDATA);
                Print(1, "added\t%s\t%u\tto cache\n", domain, ip);
                insertIP((const char *) domain, ip, answer->TTL);
            } else if (answer->TYPE == 28) {
                struct in6_addr ip = *((struct in6_addr *) answer->RDATA);
                insertIPv6((const char *) domain, ip, answer->TTL);
                Print(1, "added ipv6 address for domain %s to cache \n", domain);
            }
            free(domain);
        }
    }
}
void setHeader(DNSHeader *header) {
    header->ra = 1;
    header->rcode = 0;
    header->qr = 1;
    header->ancount = htons(1);
}
size_t dnsMessageHandler(uint8_t *start, struct sockaddr_in receive_addr, struct sockaddr_in *send_addr, const char *DNS_SERVER_IP) {
    uint8_t *end;
    DNSMessage message = parseDNSMessage(start, &end);
    int debugLevel = getDebugLevel();
    if (debugLevel == 2) {
        printDNSHeader(message.header);
    }
    Print(2, "handling dns message\n");
    if (message.header->qr == 0) {
        Question *question = message.questions;
        Print(2, "received question of TYPE %hu CLASS %hu NAME %s\n", htons(question->QTYPE), htons(question->QCLASS), question->QNAME);
        if (htons(question->QTYPE) == 1) {
            // ipv4
            domainCache *result = getIP((const char *) question->QNAME);
            if (result) {
                DNSHeader *header = message.header;
                memcpy(send_addr, &receive_addr, sizeof(receive_addr));
                if (result->ip != 0) {
                    uint32_t ip = htonl(result->ip);
                    // 本地找到对应域名，发送返回报文
                    CompressedIPAnswer *answer = (CompressedIPAnswer *) end;
                    setHeader(message.header);
                    answer->NAME = htons(0xc00c);
                    answer->TYPE = question->QTYPE;
                    answer->CLASS = question->QCLASS;
                    answer->TTL = htonl(3600);
                    answer->RDLENGTH = htons(4);
                    answer->IP = ip;
                    destroyMessage(&message);
                    return (end - start + sizeof(CompressedIPAnswer));
                } else {
                    header->ra = 1;
                    header->rcode = 3;
                    header->qr = 1;
                    destroyMessage(&message);
                    return (end - start);
                }
            }
        }
        if (htons(question->QTYPE) == 28) {
            ipv6Cache *result = getIPv6((const char *) question->QNAME);
            if (result) {
                DNSHeader *header = message.header;
                memcpy(send_addr, &receive_addr, sizeof(receive_addr));
                if (! isIPv6AllZero(&result->ip)) {
                    setHeader(message.header);
                    CompressedIPAnswer6 *answer = (CompressedIPAnswer6 *) end;
                    answer->NAME = htons(0xc00c);
                    answer->TYPE = question->QTYPE;
                    answer->CLASS = question->QCLASS;
                    answer->TTL = htonl(3600);
                    answer->RDLENGTH = htons(16);
                    answer->IP = result->ip;
                    destroyMessage(&message);
                    return (end - start + sizeof(CompressedIPAnswer6));
                } else {
                    header->ra = 1;
                    header->rcode = 3;
                    header->qr = 1;
                    destroyMessage(&message);
                    return (end - start);
                }
            }
        }
        uint16_t translatedId = idTranslation(message.header->id, receive_addr);
        message.header->id = translatedId;
        memset(send_addr, 0, sizeof(*send_addr));
        send_addr->sin_family = AF_INET;
        send_addr->sin_port = htons(DNS_SERVER_PORT);
        Print(2, "relaying dns question of TYPE %hu CLASS %hu NAME %s\n", htons(question->QTYPE), htons(question->QCLASS), question->QNAME);
        Print(2, "translate id from %hu to %hu\n", message.header->id, translatedId);
        if (inet_pton(AF_INET, DNS_SERVER_IP, &(send_addr->sin_addr)) <= 0) {
            perror("Invalid DNS server address");
            exit(1);
        }
        return end - start;
    } else {
        // 收到的是DNS应答
        uint16_t translatedId = message.header->id;
        idEntry *entry = findEntry(translatedId);
        // delete entry
        Print(1, "received response of id\t%d\t%d\n", translatedId, entry->clientID);
        message.header->id = entry->clientID;
        memcpy(send_addr, &(entry->clientAddress), sizeof(entry->clientAddress));
        // add entry to cache
        cacheEntry(message.answers, htons(message.header->ancount), start);
        cacheEntry(message.authorities, htons(message.header->arcount), start);
        return end - start;
    }
    return end - start;
}
void printDNSHeader(const DNSHeader *header) {
    printf("ID: %u\n", header->id);
    printf("Recursion Desired: %u\n", header->rd);
    printf("Truncated Message: %u\n", header->tc);
    printf("Authoritative Answers: %u\n", header->aa);
    printf("Opcode: %u\n", header->opcode);
    printf("Response Flag: %u\n", header->qr);
    printf("Response Code: %u\n", header->rcode);
    printf("Checking Disabled by Resolver: %u\n", header->cd);
    printf("Authentic Data from Named: %u\n", header->ad);
    printf("Unused Bits: %u\n", header->z);
    printf("Recursion Available: %u\n", header->ra);
    printf("Number of Question Entries: %hu\n", htons(header->qdcount));
    printf("Number of Answer Entries: %hu\n", htons(header->ancount));
    printf("Number of Authorities Entries: %hu\n", htons(header->nscount));
    printf("Number of Resource Entries: %hu\n", htons(header->arcount));
}
void destroyMessage(DNSMessage *message) {
    DNSHeader *header = message->header;
    for (uint16_t i = 0; i < ntohs(header->qdcount); i ++) {
        free(message->questions + i);
    }
}