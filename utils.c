#include <stdbool.h>
#include "utils.h"
static uint16_t nextId = 0;
static idEntry *table = NULL;
static int debugLevel;
void initTranslation() {
    nextId = (uint16_t) time(NULL);
}
uint16_t idTranslation(uint16_t clientID, struct sockaddr_in sockaddr) {
    uint16_t serverId = (nextId ++);
    addTranslationTable(serverId, clientID, sockaddr);
    return serverId;
}
void addTranslationTable(uint16_t serverId, uint16_t clientID, struct sockaddr_in clientAddress) {
    idEntry *entry = (idEntry *) malloc(sizeof(idEntry));
    entry->serverId = serverId;
    entry->clientID = clientID;
    memcpy(&(entry->clientAddress), &clientAddress, sizeof(struct sockaddr));
    idEntry *b;
    HASH_REPLACE(hh, table, serverId, sizeof(uint16_t), entry, b);

}
idEntry *findEntry(uint16_t serverId) {
    idEntry *entry;
    HASH_FIND(hh, table, &serverId, sizeof(uint16_t), entry);
    return entry;
}
void printBuffer(const uint8_t *buffer, size_t length) {
    if (debugLevel == 2) {
        for (size_t i = 0; i < length; i ++) {
            printf("%02X ", buffer[i]);
            if ((i + 1) % 16 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
}
void convertIpToDottedFormat(uint32_t ip, char *output) {
    sprintf(output, "%d.%d.%d.%d",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8) & 0xFF,
            ip & 0xFF);
}
void commandLineParser(int argc, char *argv[], char **filename, char **dns_server_ipaddr) {
    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "-d") == 0) {
            debugLevel = 1;
        } else if (strcmp(argv[i], "-dd") == 0) {
            debugLevel = 2;
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                *dns_server_ipaddr = argv[i + 1];
                i ++;  // 跳过下一个参数
            } else {
                fprintf(stderr, "Missing dns-server-ipaddr argument after -s option.\n");
                return;
            }
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                *filename = argv[i + 1];
                i ++;  // 跳过下一个参数
            } else {
                fprintf(stderr, "Missing filename argument after -f option.\n");
                return;
            }
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return;
        }
    }
    // 打印解析结果
    printf("debugLevel: %d\n", debugLevel);
    printf("dns_server_ipaddr: %s\n", *dns_server_ipaddr);
    printf("filename: %s\n", *filename);
}
uint32_t convertDottedIp(const char *ip_address) {
    struct in_addr addr;
    inet_pton(AF_INET, ip_address, &addr);
    return ntohl(addr.s_addr);
}
void Print(int dl, char *format, ...) {
    if (dl <= debugLevel) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}
int getDebugLevel() {
    return debugLevel;
}
// Function to convert domain name to DNS message format
void convertToDNSName(const char* domain, unsigned char* dnsName) {
    int position = 0;
    int length = strlen(domain);
    int i, j = 0; // Initialize j to 0

    // Iterate through the domain name
    for (i = 0; i < length; i++) {
        // Find the dot separator
        if (domain[i] == '.') {
            // Set the length of the label
            dnsName[position++] = i - j;

            // Copy the label characters
            for (; j < i; j++) {
                dnsName[position++] = domain[j];
            }

            // Update the label start position
            j++;
        }
    }

    // Set the length of the last label
    dnsName[position++] = i - j;

    // Copy the last label characters
    for (; j < i; j++) {
        dnsName[position++] = domain[j];
    }

    // Set the terminating zero-length label
    dnsName[position] = 0x00;
}
bool isIPv6AllZero(const struct in6_addr *ip) {
    for (int i = 0; i < 16; i++) {
        if (ip->s6_addr[i] != 0) {
            return 0;  // IPv6地址中存在非零字节，不全为0
        }
    }
    return 1;  // IPv6地址全为0
}
size_t convertNameToDotFormat(uint8_t *name, char *output) {
    int i = 0; // index for name
    int j = 0; // index for output
    int len = 0; // length of current label
    int offset = 0;
    while (name[i] != 0) {
        len = name[i ++]; // get the length of the next label
        if (len > 63) {
            // invalid label length, abort
            fprintf(stderr, "Invalid label length: %d\n", len);
            exit(1);
        }
        // copy the label to the output
        memcpy(output + j, name + i, len);
        j += len;
        i += len;
        // append a dot unless it is the end of the name
        if (name[i] != 0) {
            output[j ++] = '.';
        }
    }
    // terminate the output with a zero byte
    output[j ++] = 0;
    return i + 1;
}