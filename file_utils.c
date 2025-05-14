#include <stdio.h>
#include <stdlib.h>

//function read_file (file_path(get it from route function),  )

int count_chars(FILE* file_ptr){
    size_t total_chars = 0;

    while (!feof(file_ptr) && !ferror(file_ptr)){
        fgetc(file_ptr);
        total_chars++;
    }
    if (ferror(file_ptr)){
        perror("file:");
        exit(1);
    }

    return total_chars;
}


char* read_file(char* file_path){
    //file_path = ./static/index.html 
    FILE* file_ptr;
    file_ptr = fopen(file_path, "r");
    if (file_ptr == NULL){
        perror("file: ");
        exit(1);
    }


    char *html_string = malloc(count_chars(file_ptr));
    rewind(file_ptr);
    size_t index = 0;

    while (!feof(file_ptr) && !ferror(file_ptr)){
        html_string[index] = fgetc(file_ptr);
        index++;
    }
    
    if (ferror(file_ptr)){
        perror("File:");
        exit(1);
    }

    html_string[index-1] = '\0';

    fclose(file_ptr);
    
    return html_string;

}

// int main(){
//     printf("%s", read_file("./static/index.html"));

//     return 0;
// }

