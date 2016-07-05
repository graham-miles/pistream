#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include "stream_base.h"

FILE *jpeg_fd;

int main(int argc, char *argv[]) {
	parse_args(argc, argv);	
	connect_to_client();
	unsigned char buffer[atoi(argv[2])][MAX_BUFFER_SIZE];
	int i = 0;
	while (1) {
		int numread = recv_packet(buffer[i]);
		if (numread > 0) {
			printf("captured frame %d\n", i);
			char pic[128];
			sprintf(pic, "./frame%02d.jpg", i);
			jpeg_fd = fopen(pic, "wb");
			write_jpegfile(buffer[i], WIDTH, HEIGHT, 3, jpeg_fd, 100);
			i = (i + 1) % atoi(argv[2]);
		}
	}
	return 0;
}
