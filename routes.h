#ifndef ROUTES_H
#define ROUTES_H


typedef struct {
    char *uri;
    char *method;
    char *path_to_template;
} Route;

Route routes[1024];
void register_route(char* uri, char* method, char* path_to_template);
int route_exists(char *uri);
char* get_path_from_route(char* uri);

#endif 