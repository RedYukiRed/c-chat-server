#include "../include/client/chat_client.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const char *server_ip = "127.0.0.1";
    int server_port = 9001;
    
    printf("╔════════════════════════════════╗\n");
    printf("║        CHAT CLIENT             ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    if (argc >= 2) {
        server_ip = argv[1];
    }
    
    if (argc >= 3) {
        server_port = atoi(argv[2]);
        if (server_port <= 0 || server_port > 65535) {
            printf("Error: Invalid port number!\n");
            printf("Usage: %s [IP] [PORT]\n", argv[0]);
            printf("Example: %s 192.168.1.5 8080\n", argv[0]);
            return 1;
        }
    }
    
    printf("Connecting to %s:%d...\n", server_ip, server_port);
    
    start_client(server_ip, server_port);
    
    printf("Goodbye!\n");
    return 0;
}