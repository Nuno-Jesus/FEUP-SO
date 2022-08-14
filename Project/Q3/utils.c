#include "utils.h"
#include "string.h"

void get_text(char text[]){
    char chunk[CHUNK_SIZE];
    int bytes;
    strcpy(text, "");

    while (1){
        bytes = read(STDIN_FILENO, chunk, CHUNK_SIZE - 1);
        chunk[bytes] = '\0';

        strcat(text, chunk);
        if(bytes != CHUNK_SIZE - 1)
            break;
    }
}

void lower_string(char *str){
    for(int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

bool is_special(char c){
    return (c == '.' || c == ',' || c == '?' || c == '!');
}

char remove_special_character(char *str){
    char c;
    if (is_special(str[strlen(str) - 1])){
        c = str[strlen(str) - 1];
        str[strlen(str) - 1] = '\0';
        return c;
    }
    return '\0';
}

void add_special_character(char *str, char special){
    str[strlen(str)] = special;
    str[strlen(str) + 1] = '\0';
}