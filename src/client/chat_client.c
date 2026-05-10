#include "../include/common/socket_utils.h"
#include "../include/client/chat_client.h"
#include <pthread.h>

static int sock;
static volatile int connected = 1;

void *receive_messages(void *arg) {
    char buffer[1100];
    int bytes;
    
    while (connected && (bytes = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
    
    if (bytes <= 0) {
        printf("\n[Server disconnected]\n");
        connected = 0;
    }
    return NULL;
}

void start_client(const char *server_ip, int server_port) {
    char buffer[1024];
    char my_name[32];
    
    sock = connect_to_server(server_ip, server_port);
    if (sock < 0) {
        printf("Failed to connect to server!\n");
        return;
    }
    
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';
    printf("%s", buffer);
    
    fgets(my_name, sizeof(my_name), stdin);
    send(sock, my_name, strlen(my_name), 0);
    
    bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';
    printf("%s", buffer);
    
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_detach(recv_thread);
    

    char message[1024];
    while (connected) {
        if (fgets(message, sizeof(message), stdin) == NULL) break;
        if (strlen(message) <= 1) continue;
        
        if (send(sock, message, strlen(message), 0) <= 0) {
            printf("[Connection lost]\n");
            break;
        }
    }
    
    printf("[Chat ended]\n");
    close(sock);
}