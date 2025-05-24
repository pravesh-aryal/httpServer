#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include "server.h"
#include "file_utils.h"
#include "routes.h"
#include "parser.h"
#include "request.h"


volatile bool keep_running = true;

void handle_sigint(int sig) {
    (void)sig; 
    keep_running = false;
    printf("\nShutting down server gracefully...\n");
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    char buffer[1024];
    char *request_string;
    char *response_string;

    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return NULL;
    }

    buffer[bytes_received] = '\0';
    request_string = buffer;

    Request request = parseRequest(request_string);
    response_string = getParsedResponse(request);

    send(client_socket, response_string, strlen(response_string), 0);

    close(client_socket);
    return NULL;
}

Server initServer(Server server) {
    int opt = 1;

    if ((server.server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server.server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(PORT);

    return server;
}

void runServer(Server server) {
    socklen_t addrlen = sizeof(server.address);
    int client_socket;
    if (!keep_running){
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, handle_sigint);

    if (bind(server.server_socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server.server_socket, 100) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (keep_running) {
        client_socket = accept(server.server_socket, (struct sockaddr *)&server.address, &addrlen);
        if (client_socket < 0) {
            if (!keep_running) break;
            perror("accept");
            continue;
        }

        int *client_fd = malloc(sizeof(int));
        if (!client_fd) {
            perror("malloc");
            close(client_socket);
            continue;
        }

        *client_fd = client_socket;

        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, client_fd) != 0) {
            perror("pthread_create");
            close(client_socket);
            free(client_fd);
            continue;
        }

        pthread_detach(tid);
    }

    close(server.server_socket);
}
