#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include "stream_base.h"

FILE *jpeg_fd;

int main(int argc, char *argv[]) {
	jpeg_fd  = fopen("frame.jpg", "wb");
    if (jpeg_fd == NULL) {
        fprintf(stderr, "could not open output file\n");
        fprintf(stderr, "\nABORTING PROGRAM\n");
        exit(EXIT_FAILURE);
    }
	parse_args(argc, argv);	
	connect_to_client();
	unsigned char buffer[MAX_BUFFER_SIZE];
	recv_packet(buffer);
	write_jpegfile(buffer, WIDTH, HEIGHT, 3, jpeg_fd, 100);
	return 0;
}