#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <python2.7/Python.h>
#include <pthread.h>
#include "../lib/fonts/font.h"
#include "../lib/aes/aes.h"

#define SOFTWARE_NAME "IRC free client"
#define VERSION "V.0.0.1"
#define WELCOME_MESS "Welcome in IRC - Home"
#define COPYRIGHT_MESS "Copyright 2017-2018 © All rights reserved - ESGI"

#define AVAILABLE_DISPLAY "Available Commands:"
#define AVAILABLE_COMMANDS "quit: Exit the program\n"\
    "connect: Start the server\n"\
    "help: Show available commands.\n"

#define SOCKET_IP_ADDRESS "127.0.0.1"
#define SOCKET_PORT 1330

#define SIGNAL_CONNECTED   "0x003"

int socket_desc;
struct sockaddr_in server;
char server_reply[10000];
char *call_python_module_(char* mod, char* fun, char* att);
void *send_message(void *t);
void *receive_message(void *t);
void menu();
void available_commands();
void chat();
char *encrypt__(int i, char * buf, int sz);
