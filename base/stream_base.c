#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "stream_base.h"

int conn_sockfd, sockfd, port, client_len;
struct sockaddr_in addr_base, addr_client;

int recv_packet(unsigned char *buffer) {
	size_t rec = 0;
	do {
		size_t numread = read(conn_sockfd, &buffer[rec], MAX_BUFFER_SIZE - rec);
		if (numread == -1) {
			fprintf(stderr, "receive packet: FAILURE\n");
			fprintf(stderr, "\nABORTING PROGRAM\n");
			exit(EXIT_FAILURE);
		} else if (numread == 0) {
			printf("receive packet terminated; null data\n");
			break;
		} else {
			rec += numread;
		}
	}
	while (rec < MAX_BUFFER_SIZE);
	printf("packet of %d bytes successfully received\n", rec);
    return rec;
}

void parse_args(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "invalid number of arguments: %d\n", argc);
		fprintf(stderr, "usage: %s [port number] [frame count]\n", argv[0]);
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	port = atoi(argv[1]);
	printf("parsed port number: %d\n", port);
	if (port < 1) {
		fprintf(stderr, "port number validate: FAILURE\n");
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	printf("port number validate: SUCCESS\n");
	int frame_count = atoi(argv[2]);
	printf("mah\n");
	printf("parsed frame count: %d\n", frame_count);
	printf("nah\n");
	if (frame_count < 1) {
		fprintf(stderr, "frame count validate: FAILURE\n");
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	printf("frame count validate: SUCCESS\n");
}

void connect_to_client() {
	printf("initiating connection process\n");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket creation: FAILURE\n");
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	printf("socket creation: SUCCESS\n");
	memset(&addr_base, 0, sizeof(addr_base));
	addr_base.sin_family = AF_INET;
	addr_base.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr*) &addr_base, sizeof(addr_base)) < 0) {
		fprintf(stderr, "socket bind: FAILURE\n");
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	printf("socket bind: SUCCESS\n");
	if (listen(sockfd, 1) < 0) {
		fprintf(stderr, "socket listen: FAILURE\n");
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	printf("socket listen: SUCCESS\n");
	client_len = sizeof(addr_client);
	if ((conn_sockfd = accept(sockfd, (struct sockaddr*) &addr_client, (socklen_t*) &client_len)) < 0) {
		fprintf(stderr, "socket accept: FAILURE\n");
		fprintf(stderr, "\nABORTING PROGRAM\n");
		exit(EXIT_FAILURE);
	}
	printf("socket accept: SUCCESS\n");
	printf("connection fully established\n");
}