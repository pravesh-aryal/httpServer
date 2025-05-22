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
#include "parser.h"
#include "request.h"


Server initServer(Server server);
void runServer(Server server);


Server initServer(Server server){
    int opt = 1;
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
    char buffer[1024];
    char *request_string;
    char *response_string;
    socklen_t addrlen = sizeof(server.address);
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

    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes_received] = '\0';
    request_string = buffer;

    Request request = parseRequest(request_string);
    response_string = getParsedResponse(request);


    send(client_socket, response_string, strlen(response_string), 0);

    close(client_socket);
    close(server.server_socket);
}
