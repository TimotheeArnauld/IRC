#include "main.h"


int main(int argc, char** argv){
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_addr.s_addr = inet_addr(SOCKET_IP_ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons(SOCKET_PORT);

    if(connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
        return -1;

    menu();
    chat();
    return 0;
}

void menu(){
    system("clear");
    printf("%s\
            %s\n", format_string(SOFTWARE_NAME, 2, BOLD, BLUE), format_string(VERSION, 2, BOLD, GREEN));

    printf("%s\n\
            %s\n", format_string(COPYRIGHT_MESS,2, BOLD, YELLOW ), format_string(WELCOME_MESS, 2, UNDERLINED, RED));

    available_commands();
}

void available_commands(){
    __return__(3);
    printf("%s\n", format_string(AVAILABLE_DISPLAY, 2, WHITE, NORMAL));
    __return__(1);
    printf("%s\n", format_string(AVAILABLE_COMMANDS, 2, WHITE, NORMAL));
}

void chat(){
    send(socket_desc, SIGNAL_CONNECTED, strlen(SIGNAL_CONNECTED), 0);
    
    while(1){
       char s[2000];
       printf("%s\n", format_string("Nickname: ", 1, CYAN));
       printf("%s", format_string("", 2, WHITE, NORMAL));
       scanf("%s", s);
       if(strcmp(s, "quit") == 0){
        exit(0);
       }
       send(socket_desc, s, strlen(s), 0);
    }

    close(socket_desc);
}