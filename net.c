#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <err.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "net.h"
#include "jbod.h"



/* the client socket descriptor for the connection to the server */
int cli_sd = -1;

/* attempts to read n bytes from fd; returns true on success and false on
 * failure */
static bool nread(int fd, int len, uint8_t *buf) {
  int num_read = 0;
  while (num_read < len){
  	int n = read(fd,&buf[num_read],len - num_read);
  	if (n < 0){
  		fprintf(stderr, "reading from client failed..%s\n", strerror(errno));
  		return false;
  	}
  	if (n == 0)
  	{
  		printf("read successful\n");
  		return true;
  	}
  }
}

/* attempts to write n bytes to fd; returns true on success and false on
 * failure */
static bool nwrite(int fd, int len, uint8_t *buf) {
  int num_write = 0;
  while (num_write < len){
  	int n = write(fd,&buf[num_write],len - num_write);
  	if (n < 0){
  		fprintf(stderr, "writing to client failed..%s\n", strerror(errno));
  		return false;
  	}
  	if (n == 0)
  	{
  		printf("write successful\n");
  		return true;
  	}
  }
}

/* attempts to receive a packet from fd; returns true on success and false on
 * failure */
static bool recv_packet(int fd, uint32_t *op, uint16_t *ret, uint8_t *block) {
	
}

/* attempts to send a packet to sd; returns true on success and false on
 * failure */
static bool send_packet(int sd, uint32_t op, uint8_t *block) {
}

/* attempts to connect to server and set the global cli_sd variable to the
 * socket; returns true if successful and false if not. */
bool jbod_connect(const char *ip, uint16_t port) {

	struct sockaddr_in a1;

	//creating a socket
	cli_sd = socket(AF_INET,SOCK_STREAM,0);
	if (cli_sd == -1){
		printf("Socket creation failed..\n");
		return false;
	}
	else
	{
		printf("Socket creation successful..\n");
	}


	a1.sin_family = AF_INET;
	a1.sin_port = htons(JBOD_PORT);
	if (inet_pton(AF_INET,JBOD_SERVER, &a1.sin_addr) <= 0)
	{
		printf("connection failed..\n");
		return false;
	}
	else{
		printf("connection successful..\n");
	}

	if (connect(cli_sd, (struct sockaddr *)&a1, sizeof(a1)) < 0)
    {
        printf("connection failed..\n");
        return false;
    }
    else{
    	printf("connection successful..\n");
    }


}

/* disconnects from the server and resets cli_sd */
void jbod_disconnect(void) {
	close(cli_sd);
	cli_sd = -1;
}

/* sends the JBOD operation to the server and receives and processes the
 * response. */
int jbod_client_operation(uint32_t op, uint8_t *block) {
	while(1){



	}
}
