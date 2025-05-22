#ifndef PARSE_H
#include "request.h"
Request parseRequest(char *request_string);
char* getParsedResponse(Request request);
#endif