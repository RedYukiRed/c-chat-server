#include "../include/common/socket_utils.h"

// Make tcp socket
int create_server_socket(int port){
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0){
		perror("Socket Failed!!");
		exit(1);
	}

	struct sockaddr_in server_addr;
	setup_address(&server_addr, port);
	
	// Bind
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		perror("Bind Failed!!");
		exit(1);
	}
	
	// Listen
	if (listen(server_fd, 1) < 0){
		perror("Listen Failed!!");
		exit(1);
	}

	return server_fd;
}

// Complete Struct name server
void setup_address(struct sockaddr_in* addr, int port){
	memset(addr, 0, sizeof(struct sockaddr_in));

	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(port);
}

int accept_client(int server_fd){
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int client_fd = accept(server_fd,
			(struct sockaddr*)&client_addr,
			&client_len);
	if (client_fd < 0){
		perror("Accept Failed!!");
		exit(1);
	}
	
	printf("Client Connected\n");
	return client_fd;
}

int connect_to_server(const char *ip, int port){

	//create a socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror("Socket creation filed!");
		return -1;

	}

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0){
		perror("Invalid afress or addre not supported!\n");
		close(sock);
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		perror("Connection faild!\n");
		close(sock);
		return -1;
	}
	printf("Connected to server %s:%d\n", ip , port);
	return sock;
}