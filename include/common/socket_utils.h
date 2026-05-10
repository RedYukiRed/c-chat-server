#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int create_server_socket(int port);

void setup_address(struct sockaddr_in* addr, int port);

int accept_client(int server_fd);
