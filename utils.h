#ifndef DNS_SERVER_UTILS_H
#define DNS_SERVER_UTILS_H
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include "socket.h"
#include "lib/uthash.h"
#include "dns.h"

typedef struct {
    uint16_t serverId;
    uint16_t clientID;
    struct sockaddr_in clientAddress;
    UT_hash_handle hh;
} idEntry;
uint16_t idTranslation(uint16_t clientID, struct sockaddr_in sockaddr);
static void addTranslationTable(uint16_t serverId, uint16_t clientID, struct sockaddr_in clientAddress);
void initTranslation();
idEntry *findEntry(uint16_t serverId);
void printBuffer(const uint8_t *buffer, size_t length);
void convertIpToDottedFormat(uint32_t ip, char *output);
size_t convertNameToDotFormat(uint8_t *name, char *output);
void commandLineParser(int argc, char *argv[], char **filename, char **dns_server_ipaddr);
uint32_t convertDottedIp(const char *ip_address);
void convertToDNSName(const char *domain, unsigned char *dnsName);
void Print(int dl, char *fmt, ...);
int getDebugLevel();
bool isIPv6AllZero(const struct in6_addr *ip);
#endif //DNS_SERVER_UTILS_H
