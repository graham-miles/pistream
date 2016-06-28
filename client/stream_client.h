#define WIDTH 160
#define HEIGHT 120
#define MAX_BUFFER_SIZE WIDTH*HEIGHT*3
#define NB_CHAN 2

void connect_to_base();
void parse_args(int argc, char *argv[]);
int validate_ip(char *ip);
int send_packet(unsigned char *data);