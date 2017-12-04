#include "socket.h"

int clients_connected = 0;
int clients[10];

int listen_and_wait(){
    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;
    int n = 0;
    socket_desc  = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SOCKET_PORT);

    printf("%s\n", format_string("Infos: Wait for connections...", 1, CYAN));

    if(bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
        return 1;
    
    listen(socket_desc, 3);

    c = sizeof(struct sockaddr_in);

    pthread_t control_thread;
    pthread_create(&control_thread, NULL, control, (void*)NULL);

    while((client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c)) ){
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
	if(n < 10){
	  clients[n] = client_sock;
	  n++;
	}
        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) < 0)
            return 1;
    }

    if(client_sock < 0)
        return 1;

    return 0;
}

void *control(void *t){
    char message[256];
    printf("%s", format_string("irc-server:control/>> ", 2, BOLD, YELLOW));
    scanf("%s", &message[0]);
    printf("%s", format_string("", 2, WHITE, NORMAL));
    if(strstr(message, "quit") != NULL){
        exit(EXIT_SUCCESS);
    }
}

void *connection_handler(void* socket_desc){
    int sock = *(int*)socket_desc;
    int read_size;
    char *message, client_message[2000];
    int loop = 1;

    while(loop && recv(sock, client_message, 344, 0) > 0){
        if(strstr(client_message, "0x003") != NULL){
            loop = 0;
            __return__(1); 
            printf("%s\n", format_string("Infos: Wait for connections...", 1, CYAN));
            printf("Infos: %d clients is/are connected...\n", ++clients_connected);
            printf("%s", format_string("", 2, WHITE, NORMAL));
            break;
        }
    }

    while((read_size = recv(sock, client_message, 344, 0)) > 0){
        //write(sock, client_message, strlen(client_message));
        printf("Message received: %s\n", client_message);
        for(int i = 0; i < clients_connected; i++){
            send(clients[i], client_message, 344, MSG_DONTWAIT);
        }
        memset(client_message, 0, sizeof(client_message));
    }

    if(read_size == 0){
        printf("%s", format_string("", 1, RED));
        printf("%d clients is/are connected...\n", --clients_connected);
        printf("%s", format_string("", 2, WHITE, NORMAL));
        fflush(stdout);
    }else if(read_size == -1){
        perror("recv failed");
    }

    shutdown(sock, SHUT_RDWR);
    close(sock);
    free(socket_desc);
    return 0;
}

void send_command_shutdown(){
  char* buff;
  int i;
  buff[0] == 1;
  for(i=0; i<clients_connected; i++){
    if(send(clients[i], buff, sizeof(buff), MSG_DONTWAIT) == -1){
      printf("ERREUR SEND\n");
      exit(1);
    }
  }
}
