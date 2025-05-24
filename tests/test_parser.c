#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../parser.h"     
#include "../request.h"    

int main() {
    char raw_request[] =
        "GET /index.html HTTP/1.1\r\n"
        "Host: localhost:8000\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";
    Request req = parseRequest(raw_request);

    assert(strcmp(req.method, "GET") == 0);
    assert(strcmp(req.uri, "/index.html") == 0);
    assert(strcmp(req.http_version, "HTTP/1.1") == 0);
    assert(strcmp(req.headers[0].key, "Host") == 0);
    assert(strcmp(req.headers[0].value, " localhost:8000") == 0);
    assert(strcmp(req.headers[1].key, "Connection") == 0);
    assert(strcmp(req.headers[1].value, " keep-alive") == 0);

    printf("parseRequest basic test passed!\n");

    char with_carriage[] = "GET / HTTP/1.1\r\nHost: test\r\n\r\n";
    removeCarriageReturns(with_carriage);
    assert(strchr(with_carriage, '\r') == NULL);
    printf("removeCarriageReturns test passed!\n");

    return 0;
}
