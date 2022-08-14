#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include "matrix.h"
#include "utils.h"

int* map1;
int* map2;
int* res_map;

/**
 *!QUESTIONS 
 * Q1: Ficheiros com inputs desformatados?
 * Q2: Dá para colocar um wait() depois do if do child? É necessário colocar o wait depois do ciclo principal?
 * Q3: Quem imprime a matriz de resultado: o child final ou o parent?
 * Q4:
 */


/**
 * @brief Allocates a shared area memory in an integer array shape. It also copies the matrix numbers
 * into the shared area
 * 
 * @param m Matrix to be copied
 * @return The memory allocated to the matrix
 */
int* allocate_shared_matrix(matrix* m){
    custom_check(m == NULL, "NULL MATRIX. ABORTING");

    int* map = mmap(NULL, m->size*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, 0, 0);
    check(map == MAP_FAILED, "mmap");

    /* If allocation is successful, copy the matrix */
    for(int col = 0; col < m->columns; col++)
        for(int row = 0; row < m->rows; row++)
            map[at(col, row, m->columns)] = m->numbers[row][col];

    return map;

}


/**
 * @brief Releases the shared memory allocated to a matrix
 * 
 * @param map The shared area to be released
 * @param size The size of the area to release
 */
void release_shared_matrix(int* map, size_t size){
  check(munmap(map, size*sizeof(int)) < 0, "munmap");  
}


/**
 * @brief Its responsible for creating M processes to calculate the matrix in parallel.
 * Each process is assigned with a column to calculate.
 * It also prints the result, to be stored in the res matrix in the end.
 * 
 * @param res The matrix where the values from the shared area should be stored on
 */
void add_matrices(matrix* res){
    custom_check(!res, "NULL PARAMETERS. ABORTING");

    pid_t pid;
    for(int col = 0; col < res->columns; col++){
        pid = fork();
        check(pid == -1, "fork");

        /* Child */
        if(pid == 0){
            for(int row = 0; row < res->rows; row++)
                res_map[at(col, row, res->columns)] = map1[at(col, row, res->columns)] + map2[at(col, row, res->columns)];
            
            exit(EXIT_SUCCESS);
        }
    }
    
    for(int i = 0; i < res->columns; i++)
        check(waitpid(-1, NULL, 0) < 0, "waitpid");
    

    for(int row = 0; row < res->rows; row++)
        for(int col = 0; col < res->columns; col++)
            res->numbers[row][col] = res_map[at(col, row, res->columns)];

    print_matrix(res);
}

int main(int argc, char** argv){
    if(argc != 3)
        usage(argv[0]);

    FILE* f1 = open_file(argv[1]);
    FILE* f2 = open_file(argv[2]);

    matrix* m1 = read_matrix(f1);
    matrix* m2 = read_matrix(f2);
    
    custom_check(m1->rows != m2->rows || m1->columns != m2->columns, "MATRICES DIMENSIONS DON'T MATCH");

    matrix* res = new_matrix(m1->columns, m1->rows);
    
    /* Allocate shared memory for each matrix */
    map1 = allocate_shared_matrix(m1);
    map2 = allocate_shared_matrix(m2);
    res_map = allocate_shared_matrix(res);

    add_matrices(res);

    /* Release shared memory */
    release_shared_matrix(map1, m1->size);
    release_shared_matrix(map2, m2->size);
    release_shared_matrix(res_map, res->size);

    delete_matrix(m1);
    delete_matrix(m2);
    delete_matrix(res);

    fclose(f1);
    fclose(f2);

    return EXIT_SUCCESS;
}