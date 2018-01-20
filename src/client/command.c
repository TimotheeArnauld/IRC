#include "command.h"

char* command_analyse(char *s){
	if(strcmp(command, "-1") == 0){
		return "-1";
	}else{
		if(strcmp(command, "0") == 0){
			exit(0);
		}
		else{
			return command;
		}
	}

	return "-1";
} 