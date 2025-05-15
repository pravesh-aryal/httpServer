#include "server.h"
#include <stdio.h>

Server app;

int main(){
    app = init_server(app);
    register_route("/home", "GET", "./static/home.html");
    register_route("/index", "GET", "./static/index.html");
    // run(app);
}