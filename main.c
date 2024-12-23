#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "db.h"
#include "dns.h"
#include "utils.h"
#include "socket.h"

#define MAX_BUFFER_SIZE 512
#define DEFAULT_FILENAME "dnsrelay.txt"
#define DEFAULT_DNS "223.5.5.5"

int main(int argc, char *argv[]) {
    char *filename = DEFAULT_FILENAME;
    char *remoteDNSServerAddress = DEFAULT_DNS;
    commandLineParser(argc, argv, &filename, &remoteDNSServerAddress);
    staticReadIn(filename);
    initTranslation();
    SOCKET socketFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t addressLength = sizeof(clientAddress);
    uint8_t buffer[MAX_BUFFER_SIZE];

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Failed to initialize winsock");
        return 1;
    }
#endif

    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFileDescriptor == INVALID_SOCKET) {
        perror("Failed to create socket");
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(DNS_SERVER_PORT);

    if (bind(socketFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        perror("Bind failed");
        CLOSE_SOCKET(socketFileDescriptor);
        exit(1);
    }

    Print(0, "DNS Server is listening on %s:%u\n", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));

    // Handle DNS requests
    while (1) {
        Print(1, "Waiting for DNS messages\n");
        ssize_t num_bytes = recvfrom(socketFileDescriptor, (char *) buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddress, &addressLength);
        if (num_bytes == SOCKET_ERROR) {
            perror("Recvfrom failed");
            break;
        }
        Print(1, "Received DNS message\n");
        struct sockaddr_in responseAddress;
        size_t responseLength = dnsMessageHandler(buffer, clientAddress, &responseAddress, remoteDNSServerAddress);
        printBuffer(buffer,responseLength);
        if (responseLength) {
            if (sendto(socketFileDescriptor, (char *) buffer, responseLength, 0, (struct sockaddr *) &responseAddress, addressLength) < 0) {
                perror("Sendto failed");
                continue;
            }
        }
    }
    // Cleanup
    CLOSE_SOCKET(socketFileDescriptor);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}