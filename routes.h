#ifndef ROUTES_H
#define ROUTES_H


typedef struct {
    char *uri;
    char *method;
    char *path_to_template;
} Route;


void register_route(char* uri, char* method, char* path_to_template);

#endif 