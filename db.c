#include "db.h"
#ifdef _WIN32
size_t _getline_(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;
    if (lineptr == NULL || stream == NULL || n == NULL) {
        return - 1;
    }
    bufptr = *lineptr;
    size = *n;
    c = fgetc(stream);
    if (c == EOF) {
        return - 1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return - 1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return - 1;
            }
        }
        *p ++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }
    *p ++ = '\0';
    *lineptr = bufptr;
    *n = size;
    return p - bufptr - 1;
}
#define getline _getline_
#endif
static domainCache *entries = NULL;
static ipv6Cache *entriesIPv6 = NULL;
// 将dnsrelay文件读入内存
void staticReadIn(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("cannot open file\n");
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != - 1) {
        char *dottedIP = malloc(MAX_IP_LENGTH * sizeof(char));
        char *dottedDomain = malloc(MAX_DOMAIN_LENGTH * sizeof(char));
        if (sscanf(line, "%s %s", dottedIP, dottedDomain) != 2) {
            printf("Invalid line format: %s", line);
            continue;
        }
        uint8_t domain[MAX_DOMAIN_LENGTH];
        convertToDNSName(dottedDomain, domain);
        uint32_t ip = convertDottedIp(dottedIP);
        struct in6_addr ipv6;
        if (ip == 0) {
            memset(&ipv6, 0, sizeof(struct in6_addr));
            insertIP((const char *) domain, ip, UINT32_MAX);
            insertIPv6((const char *) domain, ipv6, UINT32_MAX);
        } else {
            if (inet_pton(AF_INET6, dottedIP, &ipv6) == 1) {
                insertIPv6((const char *) domain, ipv6, UINT32_MAX);
            } else {
                insertIP((const char *) domain, ip, UINT32_MAX);
            }
        }
    }
    free(line);
    fclose(file);
}
// 更新本地的dnsrelay文件
void updateStaticFile() {
    FILE *file = fopen("dnsrelay.txt", "w");
    if (file == NULL) {
        printf("无法打开 hosts 文件.\n");
        exit(1);
    }
    domainCache *s;
    for (s = entries; s != NULL; s = s->hh.next) {
        fprintf(file, "%u %s\n", s->ip, s->domain);
    }
    fclose(file);
}
// 在本地文件中写入新获得的dns entry
void addDomainMapping(const char *domain, uint32_t ip) {
    FILE *file = fopen("dnsrelay.txt", "a");
    if (file == NULL) {
        printf("unable to open cache file\n");
        exit(1);
    }
    fprintf(file, "\n%u %s", ip, domain);
}
// 查找某域名对应的IP
domainCache *getIP(const char *domain) {
    domainCache *s;
    HASH_FIND_STR(entries, domain, s);
    time_t currentTime = time(NULL);
    if (s != NULL && currentTime >= s->doom) {
        HASH_DEL(entries, s);
        free(s);
        return NULL;
    }
    return s;
}
// 在对照表中加入项
void insertIP(const char *domain, uint32_t ip, uint32_t ttl) {
    domainCache *s;
    HASH_FIND_STR(entries, domain, s);
    if (s == NULL) {
        s = malloc(sizeof(domainCache));
        memcpy(s->domain, domain, MAX_DOMAIN_LENGTH);
        s->ip = ip;
        s->doom = ttl + time(NULL);
        HASH_ADD_STR(entries, domain, s);
    }
}
// 查找某域名对应的IPv6地址
ipv6Cache *getIPv6(const char *domain) {
    ipv6Cache *s;
    HASH_FIND_STR(entriesIPv6, domain, s);
    time_t currentTime = time(NULL);
    if (s && currentTime >= s->doom) {
        HASH_DEL(entriesIPv6, s);
        free(s);
        return NULL;
    }
    return s;
}

// 在对照表中插入项
void insertIPv6(const char *domain, struct in6_addr ip, uint32_t ttl) {
    ipv6Cache *s;
    HASH_FIND_STR(entriesIPv6, domain, s);
    if (s == NULL) {
        s = malloc(sizeof(ipv6Cache));
        memcpy(s->domain, domain, MAX_DOMAIN_LENGTH);
        memcpy(&s->ip, &ip, sizeof(struct in6_addr));
        s->doom = ttl + time(NULL);
        HASH_ADD_STR(entriesIPv6, domain, s);
    }
}
