#include "main.h"


int main(int argc, char** argv){
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_addr.s_addr = inet_addr(SOCKET_IP_ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons(SOCKET_PORT);

    if(connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
        return -1;

    chat();

    return 0;
}

void chat(){
    send(socket_desc, SIGNAL_CONNECTED, strlen(SIGNAL_CONNECTED), 0);
    
    while(1){
       char s[2000];
       printf("Nickname: ");
       scanf("%s", s);
       send(socket_desc, s, strlen(s), 0);
    }

    close(socket_desc);
}