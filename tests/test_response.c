#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../response.h"

extern Response getResponse();

int main() {
    Response r = getResponse();

    assert(strcmp(r.http_version, "HTTP/1.1") == 0);
    assert(strcmp(r.status_code, "200") == 0);
    assert(strcmp(r.reason_phrase, "OK") == 0);
    assert(strcmp(r.headers[0].key, "Content-Type") == 0);
    assert(strcmp(r.headers[0].value, "text/html") == 0);
    assert(strcmp(r.headers[1].key, "Content-Length") == 0);
    assert(strcmp(r.headers[1].value, "2048") == 0);
    assert(strcmp(r.headers[2].key, "Connection") == 0);
    assert(strcmp(r.headers[2].value, "close") == 0);
    printf("tests for getResponse() passed\n");
    
    return 0;
}
