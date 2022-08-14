#ifndef STRING_PAIR_LIST_H
#define STRING_PAIR_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StringPair.h"
#include "utils.h"

/*
Data structure to represent a list of StringPairs.
*/
typedef struct StringPairList_{
    StringPair** pairs;
    int size;
} StringPairList;

/**
 *@brief Creates an empty StringPairList.
 *@return Pointer to the StringPairList created.
 */
StringPairList* new_string_pair_list();

/**
 * @brief Adds a StringPair to a StringPairList.
 * @param pair The StringPair to be added.
 * @param list The list to be added to.
 */
void add_pair(StringPair* pair, StringPairList* list);

/**
 * @brief Given a string, checks whether or not it is present in any of the StringPairs.
 composing the StringPairList.
 * @param list StringPairList to be checked.
 * @param str String to search for.
 * @param opposite If the string str is present in the list, opposite will be loaded with its antonym.
 * @return true if the string was found in the list, false otherwise.
 */
bool is_in_list(StringPairList* list, char *str, char *opposite);

/**
 * @brief Utilitary function to print a list of StringPairs
 * @param list StringPairList to be printed
 */
void print_list(StringPairList *list);

/**
 * @brief Reads file containg pairs of strings and places them in a StringPairList data structure
 * @return Pointer to the newly created StringPairList
 */
StringPairList* get_pairs();

/**
 * @brief Release previously allocated memory for the StringPairList
 * @param list StringPairList to be freed
 */
void free_list(StringPairList *list);


#endif