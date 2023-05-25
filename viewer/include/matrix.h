#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>

#define SUCCESS 0
#define FAILURE 1
#define S21_NULL (void *)NULL

typedef struct matrix_struct {
    int rows;
    int columns;
    double **matrix;
} matrix_t;

int create_matrix(int rows, int columns, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void remove_matrix(matrix_t *A);
int check_malloc_columns(matrix_t *A);
void initialize_zero(matrix_t *A);
int check_correct_matrix(matrix_t *A);

#endif  // __MATRIX_H__