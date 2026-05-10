#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

int start_chat(int client_1, int client_2);

#endif