#include <stdio.h> 
#include <string.h>
#include "request.h"

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

int main(){
    int index = 0;
    char* request_string =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:3490\r\n"
        "Connection: keep-alive\r\n"
        "Cache-Control: max-age=0\r\n"
        "sec-ch-ua: \"Not(A:Brand\";v=\"99\", \"Opera\";v=\"118\", \"Chromium\";v=\"133\"\r\n"
        "sec-ch-ua-mobile: ?0\r\n"
        "sec-ch-ua-platform: \"macOS\"\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/133.0.0.0 Safari/537.36 OPR/118.0.0.0\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\n"
        "Sec-Fetch-Site: none\r\n"
        "Sec-Fetch-Mode: navigate\r\n"
        "Sec-Fetch-User: ?1\r\n"
        "Sec-Fetch-Dest: document\r\n"
        "Accept-Encoding: gzip, deflate, br, zstd\r\n"
        "\r\n";

    char *request_copy = strdup(request_string); //cannot modify request_string
    removeCarriageReturns(request_copy);
    char* current_line = strsep(&request_copy, "\n"); //now this is the request line
    parseRequestLine(current_line);
    //rest lines are headers in key:value form
    while ( *request_copy != '\n' && (current_line = strsep(&request_copy, "\n"))){
            parseHeaderLine(current_line, index++);
    }
    
    return 0;
}