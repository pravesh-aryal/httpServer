#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3490






int main(void){
    int opt = 1, server_socket;
    int client_socket;
    ssize_t message_read; 
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from the server";


    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket creation faild");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
        perror("setsocopt: ");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    //attach server socket to PORT
    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    if ((client_socket = accept(server_socket, (struct sockaddr*)&address, &addrlen)) < 0){
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    message_read = read(client_socket, buffer, 1024-1);
    printf("%s \n", buffer);
    send(client_socket, hello, strlen(hello), 0);
    printf("Hello message sent to client \n");

    close(client_socket);
    close(server_socket);
    return 0;


}