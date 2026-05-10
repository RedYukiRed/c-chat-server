#include "server/chat_server.h"
#include <sys/select.h>


int start_chat(int client_1, int client_2) {
    char name_1[32] = {0};
    char name_2[32] = {0};
    char buffer[1024];
    char formatted[1100];
    int bytes;
    
    // Get name from client 1
    send(client_1, "Enter your name: ", 18, 0);
    bytes = read(client_1, name_1, sizeof(name_1) - 1);
    if (bytes <= 0) {
        printf("Client 1 disconnected before naming\n");
        close(client_1);
        close(client_2);
        return -1;
    }
    // Remove newline from the end of name
    if (name_1[bytes-1] == '\n') {
        name_1[bytes-1] = '\0';
    }
    printf("Client 1 named: %s\n", name_1);
    
    // Get name from client 2
    send(client_2, "Enter your name: ", 18, 0);
    bytes = read(client_2, name_2, sizeof(name_2) - 1);
    if (bytes <= 0) {
        printf("Client 2 disconnected before naming\n");
        close(client_1);
        close(client_2);
        return -1;
    }
    // Remove newline from the end of name
    if (name_2[bytes-1] == '\n') {
        name_2[bytes-1] = '\0';
    }
    printf("Client 2 named: %s\n", name_2);
    
    // Notify chat start
    char start_msg[100];
    snprintf(start_msg, sizeof(start_msg), "Chat started! You are chatting with %s\n", name_2);
    send(client_1, start_msg, strlen(start_msg), 0);
    snprintf(start_msg, sizeof(start_msg), "Chat started! You are chatting with %s\n", name_1);
    send(client_2, start_msg, strlen(start_msg), 0);
    
    // Main chat loop
    while (1) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(client_1, &read_fds);
        FD_SET(client_2, &read_fds);
        
        int max_fd = (client_1 > client_2) ? client_1 : client_2;
        select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        
        if (FD_ISSET(client_1, &read_fds)) {
            bytes = read(client_1, buffer, sizeof(buffer) - 1);
            if (bytes <= 0) {
                printf("%s disconnected\n", name_1);
                break;
            }
            buffer[bytes] = '\0';
            
            // Build message with sender's name
            snprintf(formatted, sizeof(formatted), "%s: %s", name_1, buffer);
            send(client_2, formatted, strlen(formatted), 0);
        }
        
        if (FD_ISSET(client_2, &read_fds)) {
            bytes = read(client_2, buffer, sizeof(buffer) - 1);
            if (bytes <= 0) {
                printf("%s disconnected\n", name_2);
                break;
            }
            buffer[bytes] = '\0';
            
            // Build message with sender's name
            snprintf(formatted, sizeof(formatted), "%s: %s", name_2, buffer);
            send(client_1, formatted, strlen(formatted), 0);
        }
    }
    
    close(client_1);
    close(client_2);
    return 0;
}
