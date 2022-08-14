#include "utils.h"

int at(int x, int y, int cols){
    return y * cols + x;
}

FILE* open_file(char* filename){
    FILE* f = fopen(filename, "r");
    
    char text[200];
    sprintf(text, "ERROR WHILE OPENING %s", filename);
    custom_check(f == NULL, text);

    return f;
}

void usage(char* command){
    printf("Usage: %s filename1 filename2", command);
    exit(EXIT_FAILURE);
}

void check(bool isError, char* function_name){
    if(isError){
        perror(function_name);
        exit(EXIT_FAILURE);
    }
}

void custom_check(bool isError, char* error){
    if(isError){
        printf("\n\t----- %s -----\n\n", error);
        exit(EXIT_FAILURE);
    }
}
