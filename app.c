#include "server.h"
#include <stdio.h>

Server app;

int main(){
    app = initServer(app);

    register_route("/home", "GET", "./static/home.html");

    register_route("/about", "GET", "./static/about.html");

    runServer(app); 
}