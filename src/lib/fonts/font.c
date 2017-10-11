#include "font.h"

void __return__(int nbreturn){
    int i = 0;
    char *tmp = NULL;

    tmp = (char*)malloc(nbreturn);

    for(; i < nbreturn; i++){
        strcat(tmp, "\n");
    }

    printf("%s", tmp);
    free(tmp);
}

char *format_string(char *src, int argc, ...){
    char *final_string = NULL;
    final_string = (char*)malloc(0);
    
    va_list va;
    va_start(va, argc);

    int i = 0;

    for(; i < argc; i++){
        char *tmp = va_arg(va, char*);
        final_string = (char*)realloc(final_string, strlen(final_string) + strlen(tmp));
        strcat(final_string, tmp);
    }

    final_string = (char*)realloc(final_string, strlen(final_string) + strlen(src));
    strcat(final_string, src);

    va_end(va);

    return final_string;
}
