#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../routes.h" 

int main() {

    register_route("/home", "GET", "../static/home.html");
    assert(route_exists("/home") == 1);
    assert(route_exists("/notfound") == 0);
    assert(strcmp(get_path_from_route("/home"), "../static/home.html") == 0);
    assert(strcmp(get_path_from_route("/notfound"), "") == 0);
    printf("all the route tests passed!\n");

    return 0;
}
