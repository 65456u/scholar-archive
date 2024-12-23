#ifndef DNS_SERVER_DB_H
#define DNS_SERVER_DB_H

#define MAX_DOMAIN_LENGTH 256
#define MAX_IP_LENGTH 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/uthash.h"
#include "utils.h"
typedef struct {
    char domain[MAX_DOMAIN_LENGTH];
    uint32_t ip;
    time_t doom;
    UT_hash_handle hh;
} domainCache;
typedef struct  {
    char domain[MAX_DOMAIN_LENGTH];
    struct in6_addr ip;
    time_t doom;
    UT_hash_handle hh;
} ipv6Cache;
void staticReadIn(char *filename);
domainCache * getIP(const char *domain);
void insertIP(const char *domain, uint32_t ip, uint32_t ttl);
static void addDomainMapping(const char *domain, uint32_t ip);
void updateStaticFile();
ipv6Cache *getIPv6(const char *domain);
void insertIPv6(const char *domain, struct in6_addr ip, uint32_t ttl);
#endif //DNS_SERVER_DB_H
