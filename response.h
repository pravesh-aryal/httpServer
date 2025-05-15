#ifndef RESPONSE_H
#define RESPONSE_H
#define MAX_HEADERS 1024
// HTTP/1.1 200 OK\r\n //status line
// Content-Type: text/html\r\n //headers from here.
// Content-Length: 70\r\n
// Connection: close\r\n
// \r\n
// <!DOCTYPE html>
// <html>
//   <body>
//     <h1>Hello, world!</h1>
//   </body>
// </html>

typedef struct{
    char* key;
    char* value;
} Header;

typedef struct {
    char* http_version;
    char *status_code;
    char *reason_phrase;
    Header headers[MAX_HEADERS];
} Response;

Response getResponse();

#endif