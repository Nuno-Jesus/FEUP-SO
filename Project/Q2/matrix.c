#include "matrix.h"


matrix* new_matrix(int columns, int rows){
    custom_check(columns <= 0 || rows <= 0, "MATRIX: INVALID DIMENSIONS");

    matrix* m = (matrix*) malloc(sizeof(matrix));
    check(m == NULL, "malloc");

    m->columns = columns;
    m->rows = rows;
    m->size = columns * rows;

    m->numbers = (int**) malloc(m->rows * sizeof(int*));
    check(m->numbers == NULL, "malloc");

    for(int i = 0; i < m->rows; i++){
        m->numbers[i] = (int*) calloc(m->columns, sizeof(int));
        check(m->numbers[i] == NULL, "malloc");
    } 

    return m;
}

void delete_matrix(matrix* m){
    if(m == NULL) 
        return;

    for(int i = 0; i < m->rows; i++)
        free(m->numbers[i]);

    free(m->numbers);
    free(m);
}

matrix* read_matrix(FILE* f){
    int columns = 0, rows = 0, temp = 0;

    fscanf(f, "%dx%d", &rows, &columns);
    matrix* m = new_matrix(columns, rows);

    int row = 0, col = 0, numRead = 0, res;
    while((res = fscanf(f, "%d", &temp)) != EOF){
        row = numRead / columns;
        col = numRead % columns;
        
        numRead++;

        if(!res){
            printf("\n\t----- ERROR: READING AN UNKNOWN SYMBOL -----\n\n");
            delete_matrix(m);
            exit(EXIT_FAILURE);
        }

        if(numRead > m->size){
            printf("\n\t----- ERROR: READING MORE NUMBERS THAN THE SIZE OF THE MATRIX -----\n\n");
            delete_matrix(m);
            exit(EXIT_FAILURE);
        }

        else
            m->numbers[row][col] = temp;    
    }

    if(numRead < m->size){
        printf("\n\t----- ERROR: READING LESS NUMBERS THAN THE SIZE OF THE MATRIX -----\n\n");
        delete_matrix(m);
        exit(EXIT_FAILURE);
    }

    

    return m;
}

void print_matrix(matrix* m){
    custom_check(m == NULL, "NULL PARAMETERS. ABORTING");
    
    printf("%dx%d\n", m->rows, m->columns);
    for(int row = 0; row < m->rows; row++){
        for(int col = 0; col < m->columns; col++)
            printf("%d ", m->numbers[row][col]);
        printf("\n");
    }
}