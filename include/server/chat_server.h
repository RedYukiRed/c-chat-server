#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

int start_chat(int clinet_1, int clinet_2);


#endif
