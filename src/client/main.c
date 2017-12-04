#include "main.h"

int main(int argc, char** argv){
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_addr.s_addr = inet_addr(SOCKET_IP_ADDRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(SOCKET_PORT);

	if(connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
		return -1;
	
	Py_Initialize();
	menu();
	chat();
	Py_Finalize();
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

char *call_python_module(char *mod, char *fun, char* att){
	PyObject *pName, *pModule, *pFunction, *pArg, *pValue;
	pName = PyString_FromString(mod);
	pModule = PyImport_Import(pName);
	pArg = PyTuple_New(1);
	PyTuple_SetItem(pArg, 0, PyString_FromString(att));
	pFunction = PyObject_GetAttrString(pModule, fun);
	return PyString_AsString(PyObject_CallObject(pFunction, pArg));
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
	char s[256];
	printf("%s\n", "Message >> ");
	fgets(s, sizeof(s), stdin);
	if(strcmp(s, "quit\n") == 0){
		exit(0);
	}
	char *tmp = call_python_module("aes", "encrypt", s);
	printf("%s\n", tmp);
	send(socket_desc, tmp, strlen(tmp), 0);
	memset(s, 0, sizeof(s));
}

void *receive_message(void *t){
	char message[344];
	if(recv(socket_desc, message, sizeof(message), 0) > 0){
		char *tmp = call_python_module("aes", "decrypt", message);
		if(tmp)
			printf("Message received: %s\n", tmp);
	}
	memset(message, 0, sizeof(message));
}
