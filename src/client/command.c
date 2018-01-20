#include "command.h"

char* command_analyse(char *s){
	if(strcmp(s, "-1") == 0){
		return "-1";
	}else{
		if(strcmp(s, "0") == 0){
			exit(0);
		}
		else{
			return s;
		}
	}

	return "-1";
} 