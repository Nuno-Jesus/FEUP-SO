#include "StringPairList.h"

StringPairList* new_string_pair_list(){
    StringPairList* spl = (StringPairList*) malloc(sizeof(StringPairList));
    if(spl == NULL){
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    spl->pairs = NULL;
    spl->size = 0;
    return spl;
}

void add_pair(StringPair* pair, StringPairList* list){
    list->pairs = (StringPair **) realloc(list->pairs, ++list->size * sizeof(StringPair*));
    
    if (list->pairs == NULL){
        perror("realloc()");
        exit(EXIT_FAILURE);
    }

    list->pairs[list->size - 1] = pair;
}

StringPairList* get_pairs() {
    FILE *f;
    char str1[MAX_WORD_SIZE], str2[MAX_WORD_SIZE];
    StringPairList* list = new_string_pair_list();

    f = fopen("cypher.txt", "r");

    if (f == NULL){
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    while (fscanf(f, "%s %s", str1, str2) != EOF){
        StringPair* pair = new_string_pair(str1, str2);
        add_pair(pair, list);
    }

    fclose(f);
    return list;
}


bool is_in_list(StringPairList* list, char *str, char *opposite){
    char newStr[MAX_WORD_SIZE] = {'\0'};
    strcpy(newStr, str);
    
    /* Remove terminal characters */
    char c = remove_special_character(newStr);
    lower_string(newStr);

    //puts(newStr);
    
    for (int i = 0; i < list->size; i++){
        if (is_in_pair(list->pairs[i], newStr, opposite)){
            add_special_character(opposite, c);
            return true;
        }
    }

    return false;
}

void print_list(StringPairList *list){
    for (int i = 0; i < list->size; i++)
        print_pair(list->pairs[i]);
}

void free_list(StringPairList *list){
    int len = list->size;
    
    for (int i = 0; i < len; i++){
        free_pair(list->pairs[i]);
    }
    free(list->pairs);
    free(list);
}