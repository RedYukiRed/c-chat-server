#include "../include/common/socket_utils.h"
#include "../include/server/chat_server.h"

#define PORT 9001


int main() {
    printf("Starting server on port %d...\n", PORT);

    // Create server socket
    int server_fd = create_server_socket(PORT);
    printf("Server socket created.\n");

    // Accept client
    int clinet_a = accept_client(server_fd);
    int clinet_b = accept_client(server_fd);

    start_chat(clinet_a, clinet_b);
    
    close(clinet_a);
    close(clinet_b);
    close(server_fd);

    return 0;
}

