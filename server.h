#ifndef SERVER_H
#define SERVER_H

#define MAX_ROUTES 1024
#define PORT 3490

#include "routes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    int server_socket;
    int port;
    char ip[INET_ADDRSTRLEN];
    int max_clients;
    int client_sockets[FD_SETSIZE];
    char request_buffer[8192];
    char response_buffer[8192];
    struct sockaddr_in address;
    Route routes[MAX_ROUTES];
} Server;


Server initServer(Server server);
void runServer(Server server);

#endif