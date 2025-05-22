#ifndef RESPONSE_H
#define RESPONSE_H
#include "request.h"


// typedef struct{
//     char* key;
//     char* value;
// } Header;

typedef struct {
    char* http_version;
    char *status_code;
    char *reason_phrase;
    Header headers[MAX_HEADERS];
} Response;

Response getResponse();

#endif