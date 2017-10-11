#ifndef FONT_H
#define FONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define NORMAL          "\e[0m"

#define BOLD            "\e[1m"
#define DIM             "\e[2m"
#define UNDERLINED      "\e[4m"
#define BLINK           "\e[5m" //Does not work with most of the terminal emulators
#define REVERSE         "\e[7m"
#define HIDDEN          "\e[8m"

#define DEFAULT         "\e[39m"
#define BLACK           "\e[30m"
#define RED             "\e[31m"
#define GREEN           "\e[32m"
#define YELLOW          "\e[33m"
#define BLUE            "\e[34m"
#define MAGENTA         "\e[35m"
#define CYAN            "\e[36m"
#define LIGHTGREY        "\e[37m"
#define DARKGREY        "\e[90m"
#define LIGHTRED        "\e[91m"
#define LIGHTGREEN      "\e[92m"
#define LIGHTYELLOW     "\e[93m"
#define LIGHTBLUE       "\e[94m"
#define LIGHTMAGENTA    "\e[95m"
#define LIGHTCYAN       "\e[96m"
#define WHITE           "\e[97m"

#define B_DEFAULT       "\e[49m"
#define B_BLACK         "\e[40m"
#define B_RED           "\e[41m"
#define B_GREEN         "\e[42m"
#define B_YELLOW        "\e[43m"
#define B_BLUE          "\e[44m"
#define B_MAGENTA       "\e[45m"
#define B_CYAN          "\e[46m"
#define B_LIGHTGREY     "\e[47m"
#define B_DARKGREY      "\e[100m"
#define B_LIGHTRED      "\e[101m"
#define B_LIGHTGREEN    "\e[102m"
#define B_LIGHTYELLOW   "\e[103m"
#define B_LIGHTBLUE     "\e[104m"
#define B_LIGHTMAGENTA  "\e[105m"
#define B_LIGHTCYAN     "\e[106m"
#define B_WHITE         "\e[107m"

void __return__(int nbreturn);
char *format_string(char* src, int argc, ...);

#endif
