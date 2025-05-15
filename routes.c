#include "routes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <file_utils.h>


int index = 0;

void register_route(char* uri, char* method, char* path_to_template){
    routes[index].uri = uri;
    routes[index].method = method;
    routes[index].path_to_template = path_to_template;  
    index++;  
}

int route_exists(char *uri){
    for (int i = 0; i < index; i++){
        if (strcmp(routes[i].uri, uri) == 0) { //if route exists
            return 1;
        }
    }
    return 0; //if route DNE
}


//main is for testing purpose during development
// int main(){

// }