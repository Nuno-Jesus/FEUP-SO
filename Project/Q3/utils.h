#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include "string.h"

#include "StringPairList.h"
#include "StringPair.h"

#define CHUNK_SIZE 256
#define MAX_TEXT_SIZE 4096
#define MAX_WORD_SIZE 25

/**
 *@brief Utilitary functions that reads input from the Standard Input.
 *@param text Contains the data read from the standard input.
 */
void get_text(char text[]);

/**
 *@brief Given a string str, returns its lowercase representation.
 *@param str String to lowercase.
 */
void lower_string(char *str);

/**
 *@brief Given a character, checks if it is a punction mark.
 *@param c Character to check.
 *@return true if c is a punction mark, false otherwise.
 */
bool is_special(char c);

/**
 *@brief Given a string, removes its special characters, if present.
 *@param str String to be changed.
 *@return If any character was removed, returns it. Otherwise, returns the null terminator '\0'.
 */
char remove_special_character(char *str);

/**
 *@brief Given a string, adds a character at its end.
 *@param str String to be changed.
 *@param c Character to be added
 */
void add_special_character(char *str, char special);

#endif /* UTILS_H */
