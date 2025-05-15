#include "server.h"
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "routes.h"
#include "server.h"


Server initServer(){
    int opt = 1;
    Server server;
    socklen_t addrlen = sizeof(server.address);
    ssize_t response_string;
    char buffer[1024] = {0};

    if ((server.server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket: ");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server.server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
        perror("setsockopt; ");
        exit(EXIT_FAILURE);
    }

    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(PORT);

    return server;

}

void runServer(Server server){
    int client_socket;
    if (bind(server.server_socket, (struct sockaddr*)&server.address, sizeof(server.address)) < 0){
        perror("bind:");
        exit(EXIT_FAILURE);
    }
    if (listen(server.server_socket, 3) < 0){
        perror("listen:");
        exit(EXIT_FAILURE);
    }

    if ((client_socket = accept(server.server_socket, (struct sockaddr*)&server.address, &addrlen)) < 0){
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    request_string = read(client_socket, buffer, 1024-1);
    printf("%s \n", buffer);
    send(client_socket, response_string, strlen(response_string), 0);

    close(client_socket);
    close(server.server_socket);
}
