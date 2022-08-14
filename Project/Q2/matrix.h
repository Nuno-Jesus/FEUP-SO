#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


typedef struct{
    int columns, rows, size;
    int** numbers;
} matrix;

/**
 * @brief Allocates a new instance of a matrix struct pointer
 * 
 * @param columns Number of columns of the new matrix
 * @param rows Number of rows of the new matrix
 * @return The pointer to the newly created matrix 
 */
matrix* new_matrix(int columns, int rows);

/**
 * @brief Releases the memory allocated to the given matrix
 * @param m The matrix to be freed
 */
void delete_matrix(matrix* m);

/**
 * @brief Given a file pointer, it reads integers from a file and assembles a 
 * new matrix.
 * 
 * @param f The file pointer to be read
 * @return A new matrix with the values read from the file pointer
 */
matrix* read_matrix(FILE* f);

/**
 * @brief Displays a matrix with a matrix format
 * @param m The matrix to be displayed
 */
void print_matrix(matrix* m);

#endif