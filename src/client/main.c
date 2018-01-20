#include <ncurses.h>
#include "main.h"

WINDOW *create_newwin(int h, int w, int x, int y, int border);
void destroy_win(WINDOW *local_win);

int main(int argc, char** argv){
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_addr.s_addr = inet_addr(SOCKET_IP_ADDRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(SOCKET_PORT);

	if(connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
		return -1;
	
	initscr();
	start_color();
	raw();
	Py_Initialize();
	menu();
	chat();
	Py_Finalize();
	endwin();

	return 0;
}

void menu(){
	int row, col;
	getmaxyx(stdscr, row, col);

	WINDOW *menu_win = create_newwin(8, col, 0, 0, 1);

	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	wattron(menu_win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(menu_win, 1, 1, SOFTWARE_NAME);
	wattroff(menu_win, A_BOLD | COLOR_PAIR(1));

	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	wattron(menu_win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(menu_win, 2, 1, VERSION);
	wattroff(menu_win, A_BOLD | COLOR_PAIR(2));

	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	wattron(menu_win, A_BOLD | COLOR_PAIR(3));
	mvwprintw(menu_win, 3, 1, COPYRIGHT_MESS);
	wattroff(menu_win, A_BOLD | COLOR_PAIR(3));

	init_pair(4, COLOR_RED, COLOR_BLACK);
	wattron(menu_win, COLOR_PAIR(4));
	mvwprintw(menu_win, 4, 1, WELCOME_MESS);
	wattroff(menu_win, COLOR_PAIR(4));

	mvwprintw(menu_win, 5, 1, "Enter /help to see available commands.");	
	wrefresh(menu_win);
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
		
	pthread_create(&send_thread, NULL, send_message, (void*)NULL);
	pthread_create(&received_thread, NULL, receive_message, (void*)NULL);

	pthread_join(send_thread, NULL);
	pthread_join(received_thread, NULL);

	close(socket_desc);
}

void *send_message(void *t){
	int col, row;
	getmaxyx(stdscr, row, col);
	
	WINDOW *input_win = create_newwin(3, col, row - 3, 0, 1);	

	while(1){
		fflush(stdin);
		wclear(input_win);
		wborder(input_win, '|', '|', '-', '-', '+', '+', '+', '+');
		mvwprintw(input_win, 1, 1, "Message>>");
		char s[256];
		mvwgetstr(input_win, 1, sizeof("Message>>") + 1, s);

		char *cmd = command_analyse(s);
		if(strcmp(cmd, "-1") == 0){
			printf("Bad instruction or command. Type /help to see available commands");
		}else{
			char *tmp =  call_python_module("aes", "encrypt", cmd);
			send(socket_desc, tmp, 344, 0);
			memset(tmp, 0, 344);
			memset(s, 0, 256);
		}
	}
	destroy_win(input_win);
}

void *receive_message(void *t){
	int col, row;
	getmaxyx(stdscr, row, col);
	
	WINDOW *chat_win = create_newwin(10, col, 10, 0, 0); 
	scrollok(chat_win, TRUE);
	wclear(chat_win);
	wrefresh(chat_win);

	while(1){
		char message[344];
		if(recv(socket_desc, message, 344, 0) > 0){
			char *tmp = call_python_module("aes", "decrypt", message);
			if(tmp){
				wprintw(chat_win, "%s\n", tmp);
				wrefresh(chat_win);
			}
		}
		memset(message, 0, 344);
	}
}

WINDOW *create_newwin(int h, int w, int  x, int y, int border){
	WINDOW *local_win;
	local_win = newwin(h, w, x, y);
	if(border == 1){
		wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
	}else{
		wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	}
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win){
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}
