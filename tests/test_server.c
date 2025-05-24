#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <assert.h>
#include "../server.h"

#define PORT 3490 
extern Server initServer(Server server);
extern void runServer(Server server);

void *start_server(void *arg) {
    Server server = initServer(*(Server *)arg);
    runServer(server);
    return NULL;
}

int main() {

    pthread_t server_thread;
    Server server;
    pthread_create(&server_thread, NULL, start_server, &server);

    sleep(1); 
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    assert(client_socket >= 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    assert(connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0);

    const char *request =
        "GET /home HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";
    send(client_socket, request, strlen(request), 0);

    char response[4096];
    ssize_t bytes = recv(client_socket, response, sizeof(response) - 1, 0);
    response[bytes] = '\0';

    assert(strstr(response, "HTTP/1.1 200 OK") != NULL);
    printf("Server responded successfully:\n%s\n", response);

    close(client_socket);
    printf("test_server tests passed!\n");
    return 0;
}
