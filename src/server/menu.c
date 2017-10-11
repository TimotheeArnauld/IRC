#include "menu.h"

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

    wait_for_command();
}

void wait_for_command(){
    int loop = 1;
    char message[256];

    while(loop){
        printf("%s", format_string("irc-server:$/>>  ", 2, BOLD, BLUE));
        printf("%s", format_string("", 2, WHITE, NORMAL));
        scanf("%s", &message[0]);
        if(select_command(message) == 0){
            printf("%s", format_string("Not recognized options. Please try help to see available commands.\n", 1, RED));
        }
    }
}

int select_command(char *src){
    if(strcmp(src, "quit") == 0){
        __return__(2);
        printf("%s\n", format_string("Bye! See you soon ;)", 2, BOLD, GREEN));
        exit(EXIT_SUCCESS);
    }

    if(strcmp(src, "help") == 0){
        available_commands();
        return 1;
    }

    if(strcmp(src, "start") == 0){
        listen_and_wait();
        return 1;
    }

    if(strcmp(src, "shutdown") == 0){
      send_command_shutdown();
      return 1;
    }

    if(strcmp(src, "clear") == 0){
        system("clear");
    }

    return 0;
}
