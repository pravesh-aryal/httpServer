#include "routes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "file_utils.h"


int length = 0;

void register_route(char* uri, char* method, char* path_to_template){
    routes[length].uri = uri;
    routes[length].method = method;
    routes[length].path_to_template = path_to_template;  
    length++;  
}

int route_exists(char *uri){
    for (int i = 0; i < length; i++){
        if (strcmp(routes[i].uri, uri) == 0) { //if route exists
            printf("Route exists: %s \n", routes[i].uri);
            return 1;
        }
    }
    return 0; //if route DNE
}

char* get_path_from_route(char *uri){
    for (int i = 0; i < length; i++){
        if (strcmp(routes[i].uri, uri) == 0){
            return routes[i].path_to_template;
        }
    }
    return "";
}
