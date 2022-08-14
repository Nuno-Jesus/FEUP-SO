#ifndef STRING_PAIR_H
#define STRING_PAIR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
Data structure containing two Strings
*/
typedef struct StringPair_{
    char *str1;
    char *str2;
} StringPair;

/**
 * @brief Creates an instance of StringPair
 * @param str1 String 1
 * @param str2 String 2
 * @return Pointer to the created StringPair, NULL if an error occurs
 */
StringPair* new_string_pair(char* str1, char* str2);

/**
 * @brief Checks if the string str is present in the StringPair pair
 * @param pair StringPair to be checked
 * @param str String to be checked
 * @param opposite If the string str is present in the pair, opposite will be loaded with its antonym
 * @return true if the string is in the pair, false otherwise
 */
bool is_in_pair(StringPair* pair, char *str, char *opposite);

/**
 * @brief Utilitary function to print a StringPair
 * @param pair Pair to be printed
 */
void print_pair(StringPair* pair);


/**
 * @brief Release previously allocated memory for the StringPair
 * @param pair pair to be freed
 */
void free_pair(StringPair* pair);

#endif /* STRING_PAIR_H*/