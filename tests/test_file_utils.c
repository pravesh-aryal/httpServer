#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../file_utils.h"

extern int count_chars(FILE* file_ptr);
extern char* get_html_from_file(char* file_path);

int main(){
    FILE* fp; 
    fp = fopen("sample.txt", "r");
    assert(count_chars(fp) == 27);
    assert(strcmp(get_html_from_file("sample.html"), "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Sample</title>\n</head>\n<body>\n    Sample\n</body>\n</html>") == 0);
    printf("test_file_utils tests passed. \n");

    return 0;
}