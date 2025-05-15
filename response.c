#include "routes.h"
#include "response.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "file_utils.h"

Response getResponse(){
    Response response;
    response.http_version = "HTTP/1.1";
    response.status_code = "200";
    response.reason_phrase = "OK";
    response.headers[3];
    response.headers[0].key = "Content-Type";
    response.headers[0].value = "text/html";
    response.headers[1].key = "Content-Length";
    response.headers[1].value = "2048"; //need to calculate dummy value for now
    response.headers[2].key = "Connection";
    response.headers[2].value = "close";
    //also make response have a file_pointer in struct point that is pointed to corresponding correct html file according to the reigstered route.
    return response;
}




