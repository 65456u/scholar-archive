#ifndef DNS_SERVER_DNS_H
#define DNS_SERVER_DNS_H
#include <stdint.h>
#include "socket.h"
#include "db.h"
#define MAX_NAME_LENGTH 256
#define DNS_HEADER_OFFSET 12
#define DNS_SERVER_PORT 53
// DNS 报头 flags 领域定义
typedef struct {
    unsigned id: 16;    /* query identification number */
    unsigned rd: 1;     /* recursion desired */
    unsigned tc: 1;     /* truncated message */
    unsigned aa: 1;     /* authoritive answers */
    unsigned opcode: 4; /* purpose of message */
    unsigned qr: 1;     /* response flag */
    unsigned rcode: 4;  /* response code */
    unsigned cd: 1;     /* checking disabled by resolver */
    unsigned ad: 1;     /* authentic data from named */
    unsigned z: 1;      /* unused bits, must be ZERO */
    unsigned ra: 1;     /* recursion available */
    uint16_t qdcount;       /* number of questions entries */
    uint16_t ancount;       /* number of answers entries */
    uint16_t nscount;       /* number of authorities entries */
    uint16_t arcount;       /* number of resource entries */
} DNSHeader;
// Question 部分定义
typedef struct {
    uint8_t *QNAME; // Query name
    uint16_t QTYPE; // Query type
    uint16_t QCLASS; // Query class
} Question;
// 资源记录部分定义
typedef struct {
    uint8_t *NAME; // Resource name
    uint16_t TYPE; // Resource type
    uint16_t CLASS; // Resource class
    uint32_t TTL; // Time to live
    uint16_t RDLENGTH; // Resource data length
    uint8_t *RDATA; // Pointer to resource data
} ResourceRecord;
// DNS message 定义

typedef struct {
    DNSHeader *header;
    Question *questions;
    ResourceRecord *answers;
    ResourceRecord *authorities;
    ResourceRecord *additionalRecords;
} DNSMessage;
#pragma pack(1)
typedef struct {
    uint16_t NAME;
    uint16_t TYPE;
    uint16_t CLASS;
    uint32_t TTL;
    uint16_t RDLENGTH;
    uint32_t IP;
} CompressedIPAnswer;
typedef struct {
    uint16_t NAME;
    uint16_t TYPE;
    uint16_t CLASS;
    uint32_t TTL;
    uint16_t RDLENGTH;
    struct in6_addr IP;
} CompressedIPAnswer6;
#pragma pack()
DNSMessage parseDNSMessage(uint8_t *datagram, uint8_t **end);
void parseResourceRecord(uint8_t **begin, ResourceRecord *rr);
void parseResourceRecordFields(uint8_t **ptr, ResourceRecord **records, uint16_t count);
void cacheEntry(ResourceRecord *rrs, uint16_t count, uint8_t *start);
size_t dnsMessageHandler(uint8_t *start, struct sockaddr_in receive_addr, struct sockaddr_in *send_addr, const char *DNS_SERVER_IP);
void printDNSHeader(const DNSHeader *header);
void destroyMessage(DNSMessage * message);
#endif //DNS_SERVER_DNS_H

