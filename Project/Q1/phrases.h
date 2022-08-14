#include <stdbool.h>

/**
 * @brief Checks if c is any of the following: <.> // <?> // <!>
 * @param c Character to check
 * @return true if the character marks the end of a sentence
 * @return false otherwise
 */
bool is_terminal(char c);

/**
 * @brief Prints in the terminal the number of the phrase in the following manner: [n]
 * @param n Phrase number
 */
void print_phrase_no(int n);

/**
 * @brief If list_phrases is set to true, prints phrases from the file f in the terminal, 
 * otherwise prints only the number of phrases found.
 * @param f File stream
 * @param list_phrases Flag
 */
void read_phrases(FILE *f, bool list_phrases);