#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "StringPair.h"

StringPair* new_string_pair(char* str1, char* str2){
    StringPair* sp = (StringPair*) malloc(sizeof(StringPair));
    if(sp == NULL){
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    sp->str1 = (char*) malloc(strlen(str1) + 1);
    if(sp->str1 == NULL){
        free(sp);
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    sp->str2 = (char*) malloc(strlen(str2) + 1);
    if (sp->str2 == NULL){
        free(sp);
        free(sp->str1);
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    strcpy(sp->str1, str1);
    strcpy(sp->str2, str2);

    return sp;
}

bool is_in_pair(StringPair* pair, char *str, char *opposite){
    /* Check if str is equal to the first string of the pair */
    if (!strcmp(pair->str1, str)){
        strcpy(opposite, pair->str2);
        return true;
    }

    /* Check if str is equal to the second string of the pair */
    else if (!strcmp(pair->str2, str)){
        strcpy(opposite, pair->str1);
        return true;
    }

    return false;
}

void print_pair(StringPair* pair){
    printf("%s %s\n", pair->str1, pair->str2);
}


void free_pair(StringPair* pair){
    //print_pair(pair);
    free(pair->str1);
    free(pair->str2);
    free(pair);
}