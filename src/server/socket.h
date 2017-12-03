#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "../lib/fonts/font.h"

#define SOCKET_IP_ADDRESS "127.0.0.1"
#define SOCKET_PORT 1330

#define MAX_BUFFER 10000

typedef struct{
    char *malware_name;
}Controler;

typedef struct{
    int sockfd;
    int newsockfd;
    int clilen;
    char buffer[MAX_BUFFER];
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
}SocketControler;

int listen_and_wait();
void send_command_shutdown();
void* connection_handler(void* socket_desc);
void *control(void *);
#endif
