#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>

#include "../lib/fonts/font.h"
#include "socket.h"

#define SOFTWARE_NAME "IRC free server"
#define VERSION "V.0.0.1"
#define WELCOME_MESS "Welcome in IRC - Home"
#define COPYRIGHT_MESS "Copyright 2017-2018 © All rights reserved - ESGI"

#define AVAILABLE_DISPLAY "Available Commands:"
#define AVAILABLE_COMMANDS "quit: Exit the program\n"\
    "start: Start the server\n"\
    "shutdown: Stop the server\n"\
    "help: Show available commands.\n"

void menu(void);
void available_commands(void);
void wait_for_command(void);
int select_command(char*);

#endif
