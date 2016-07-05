#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stream_client.h"

int sockfd;
char *hostname, *port;
struct sockaddr_in addr_base, addr_client;

int send_packet(unsigned char *data) {
        int size = MAX_BUFFER_SIZE;
        printf("attempting to send packet of size: %d\n", size);
        if (size < 1) {
                printf("send packet terminated; null data\n");
                return 0;
        }
        size_t bytes = write(sockfd, data, size);
        if (bytes < 1) {
                fprintf(stderr, "write to socket: FAILURE\n");
                return -1;
        } else {
                printf("packet of %d bytes successfully sent\n", bytes);
                return bytes;
        }
}

int validate_ip(char *ip) {
        if (!strcmp("localhost", ip)) return 1;
        struct sockaddr_in sa;
        return inet_pton(AF_INET, ip, &(sa.sin_addr)) != 0;
}

void parse_args(int argc, char *argv[]) {
        if (argc != 3) {
                fprintf(stderr, "invalid number of arguments: %d\n", argc);
                fprintf(stderr, "usage: %s [hostname] [port number]\n", argv[0]);
                fprintf(stderr, "\nABORTING PROGRAM\n");
                exit(EXIT_FAILURE);
        }
        hostname = argv[1];
        printf("parsed hostname: %s\n", hostname);
        if (!validate_ip(hostname)) {
                fprintf(stderr, "hostname validate: FAILURE\n");
                fprintf(stderr, "\nABORTING PROGRAM\n");
                exit(EXIT_FAILURE);
        }
        printf("hostname validate: SUCCESS\n");
        port = argv[2];
        printf("parsed port number: %s\n", port);
        if (atoi(port) < 1) {
                fprintf(stderr, "port number validate: FAILURE\n");
                fprintf(stderr, "\nABORTING PROGRAM\n");
                exit(EXIT_FAILURE);
        }
        printf("port number validate: SUCCESS\n");
}

void connect_to_base() {
        printf("initiating connection process\n");
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                fprintf(stderr, "socket creation: FAILURE\n");
                fprintf(stderr, "\nABORTING PROGRAM\n");
                exit(EXIT_FAILURE);
        }
        printf("socket creation: SUCCESS\n");
        struct addrinfo *result;
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = 0;
        hints.ai_protocol = 0;
        if (getaddrinfo(hostname, port, &hints, &result) < 0) {
                fprintf(stderr, "network address translate: FAILURE\n");
                fprintf(stderr, "\nABORTING PROGRAM\n");
                exit(EXIT_FAILURE);
        }
        printf("network address translate: SUCCESS\n");
        if (connect(sockfd, result->ai_addr, result->ai_addrlen) < 0) {
                fprintf(stderr, "socket connect: FAILURE\n");
                fprintf(stderr, "\nABORTING PROGRAM\n");
                exit(EXIT_FAILURE);
        }
        printf("socket connect: SUCCESS\n");
        printf("connection fully established\n");
}
