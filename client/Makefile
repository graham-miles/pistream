CC = gcc
LD_FLAGS = -lc -ljpeg
LDFLAGS= #-lrt

test_logi_cam: frame_feed.c stream_client.c wishbone_wrapper.c jpeg_func.c logi_loader.c i2c_loader.c bit_bang_loader.c
	$(CC) $(LDFLAGS) -DLOGIPI -o  logi_loader logi_loader.c i2c_loader.c bit_bang_loader.c
	$(CC) -D LOGIPI -o $@ frame_feed.c stream_client.c wishbone_wrapper.c jpeg_func.c $(LD_FLAGS)

clean:
	rm -f *.a *.o test_logi_cam
	rm -rf *o logi_loader
