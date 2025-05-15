#ifndef SERVER_H
#define SERVER_H

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
    int clinet_sockets[FD_SETSIZE];
    char request_buffer[8192];
    char response_buffer[8192];

} Server;


Server init_server();
void run();

#endif