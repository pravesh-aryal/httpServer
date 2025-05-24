#ifndef PARSE_H
#include "request.h"
Request parseRequest(char *request_string);
char* getParsedResponse(Request request);
void parseRequestLine(char* request_line);
void parseHeaderLine(char *header_line, int index);
void removeCarriageReturns(char *requestString);
Request parseRequest(char *request_string);
#endif