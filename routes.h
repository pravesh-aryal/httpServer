#ifndef ROUTES_H
#define ROUTES_H
#define MAX_ROUTES 1024


typedef struct {
    char *uri;
    char *method;
    char *path_to_template;
} Route;

Route routes[MAX_ROUTES] = {0};

void register_route(char* uri, char* method, char* path_to_template);

#endif 