#include <stdio.h> 
#include <string.h>
#include "request.h"
#include "response.h"
#include "routes.h"
#include "file_utils.h"
#include <stdlib.h>
Request request;

void parseRequestLine(char* request_line){
    request.method = strsep(&request_line, " "); //GET
    request.uri = strsep(&request_line, " "); // home/page/page1.1/
    request.http_version = strsep(&request_line, " "); // HTTP/1.1
}


void parseHeaderLine(char *header_line, int index){
    request.headers[index].key = strsep(&header_line, ":"); // Host
    request.headers[index].value = strsep(&header_line, "\0");// 127.0.0.1:8008
}


void removeCarriageReturns(char *requestString){
    char *source = requestString;
    char *destination = requestString;

    while (*source != '\0') {
        if (*source != '\r') {
            *destination++ = *source;
        }
        source++;
    }
    *destination = '\0';  
}

Request parseRequest(char *request_string){
    int index = 0;
    char *request_copy = strdup(request_string); //cannot modify request_string
    removeCarriageReturns(request_copy);
    char* current_line = strsep(&request_copy, "\n"); //now this is the request line
    parseRequestLine(current_line);
    //rest lines are headers in key:value form
    while ( *request_copy != '\n' && (current_line = strsep(&request_copy, "\n"))){
            parseHeaderLine(current_line, index++);
    }
    return request;
}

char* getParsedResponse(Request* request) {
    const char* body;
    printf("File path: %s \n", request->uri);
    if (route_exists(request->uri)){
        printf("Get path from route: %s \n", get_path_from_route(request->uri));
        body = get_html_from_file(get_path_from_route(request->uri));
    }

    const char* content_type = "text/html";
    int body_len = strlen(body);

    size_t response_size = 1024 + body_len;
    char* response = (char*)malloc(response_size);
    if (!response) return NULL;

    snprintf(response, response_size,
        "%s 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        request->http_version ? request->http_version : "HTTP/1.1",
        content_type,
        body_len,
        body
    );

    return response;
}

