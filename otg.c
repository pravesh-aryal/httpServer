#include <stdio.h>

int main(){
    printf("HEllo world");
    perror("hi");
    char *hello = "<h1>Hello from the server</h1>";
    printf("%s", hello);
    return 0;
}