#include "../include/socket_utils.h"
#include "../include/chat_server.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9001

void handle_echo(int clinet_fd){
    char buffer[1024];
    int bytes_read;

    send(clinet_fd, "Server is ready!! type someting...\n", 38, 0);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        bytes_read = read(clinet_fd, buffer, sizeof(buffer) - 1);

        if (bytes_read <= 0) {
            break;
        }

        send(clinet_fd, buffer, bytes_read, 0);
    }

}

int main() {
    printf("Starting server on port %d...\n", PORT);

    // Create server socket
    int server_fd = create_server_socket(PORT);
    printf("Server socket created.\n");

    // Accept client
    int clinet_a = accept_client(server_fd);
    int clinet_b = accept_client(server_fd);

    //printf("Clinet accepted! FD = %d\n", clinet_a);
   //printf("Clinet accepted! FD = %d\n", clinet_b);
    start_chat(clinet_a, clinet_b);
    //char msg[] = "Hello from server!\n";
    //send(client_fd, msg, strlen(msg), 0);
    
    //handle_echo(clinet_fd);
    close(clinet_a);
    close(clinet_b);
    close(server_fd);

    return 0;
}

