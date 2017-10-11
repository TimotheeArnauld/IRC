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
	printf("%s\n", format_string(AVAILABLE_DISPLAY, 2, WHITE, NORMAL));
	printf("%s\n", format_string(AVAILABLE_COMMANDS, 2, WHITE, NORMAL));
}

void chat(){
	send(socket_desc, SIGNAL_CONNECTED, strlen(SIGNAL_CONNECTED), 0);
	pthread_t send_thread;
	pthread_t received_thread;

	while(1){
		fflush(stdin);
		pthread_create(&send_thread, NULL, send_message, (void*)NULL);
		receive_message(NULL);
	}
	close(socket_desc);
}

void *send_message(void *t){
	char s[2000];
	printf("%s\n", "Message >> ");
	fgets(s, sizeof(s), stdin);
	if(strcmp(s, "quit\n") == 0){
		exit(0);
	}
	send(socket_desc, s, strlen(s), 0);
	memset(s, 0, sizeof(s));
}

void *receive_message(void *t){
	char message[2000];
	if(recv(socket_desc, message, 2000, 0) > 0){
		printf("Message received: %s\n", message);
	}
	memset(message, 0, sizeof(message));
}