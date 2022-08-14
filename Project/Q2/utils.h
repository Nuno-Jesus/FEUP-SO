#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Calculates the index in a 1D array given the coordinates of a 2D array
 * 
 * @param x Horizontal coordinate
 * @param y Vertical coordinate
 * @param cols Number of columns of the 2D array
 * @return The translated index
 */
int at(int x, int y, int cols);

/**
 * @brief Opens a file with the name passed in the parameters
 * 
 * @param filename The name of the file to be opened
 * @return A file pointer to the opened
 */
FILE* open_file(char* filename);

/**
 * @brief Prints how to run the program, in case the program runs without the
 * right number of arguments in the console
 * 
 * @param command Name of the executable
 */
void usage(char* command);


/**
 * @brief Given an to be checked after a function was executed, it checks
 * if error condition is true, it prints the error with perror() and exits the program.
 * 
 * @param isError Error condition 
 * @param function_name Function name where the error occured
 */
void check(bool isError, char* function_name);

/**
 * @brief It prints a custom message, if the error condition is true
 * 
 * @param isError Error condition
 * @param error Message to be displayed
 */
void custom_check(bool isError, char* error);

#endif