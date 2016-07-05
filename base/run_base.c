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
	unsigned char buffer[atoi(argv[2])][MAX_BUFFER_SIZE];
	int i = 0;
	while (1) {
		int numread = recv_packet(buffer[i]);
		if (numread > 0) {
			char * pic;
			sprintf(pic, "frame%d.jpg", i);
			jpeg_fd = fopen(pic, "wb");
			write_jpegfile(buffer[i], WIDTH, HEIGHT, 3, jpeg_fd, 100);
			i++;
		}
	}
	// recv_packet(buffer);
	// write_jpegfile(buffer, WIDTH, HEIGHT, 3, jpeg_fd, 100);

	// int num = atoi(argv[1]);
	// printf("Num: %d", num);
	// unsigned char buffer[num][50];
	// strncpy(buffer[0], "hello, ", sizeof(buffer[0]));
	// strncpy(buffer[1], "my ", sizeof(buffer[1]));
	// strncpy(buffer[2], "name ", sizeof(buffer[2]));
	// strncpy(buffer[3], "is ", sizeof(buffer[3]));
	// strncpy(buffer[4], "graham ", sizeof(buffer[4]));
	// for (int i = 0; i < num; i++) {
	// 	printf("\n%d: %s", i, buffer[i]);
	// }
	return 0;
}
