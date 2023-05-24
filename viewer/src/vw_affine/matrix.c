#include "../../include/matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int answer = SUCCESS;
  if (rows <= 0 || columns <= 0) answer = FAILURE;
  if (answer == SUCCESS) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
      }
    } else {
      answer = FAILURE;
    }
  }
  if (answer == SUCCESS) {
    answer = check_malloc_columns(result);
    if (answer == FAILURE) remove_matrix(result);
  }
  if (answer == SUCCESS) {
    initialize_zero(result);
  }
  return answer;
}

int check_malloc_columns(matrix_t *A) {
  int answer = SUCCESS;
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] == NULL) {
      answer = FAILURE;
    }
  }
  return answer;
}

int check_correct_matrix(matrix_t *A) {
  int answer = SUCCESS;
  if (!A) answer = FAILURE;
  if (answer == SUCCESS) {
    if (!(A->matrix)) {
      answer = FAILURE;
    }
  }
  return answer;
}


void initialize_zero(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = 0.;
    }
  }
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int answer = check_correct_matrix(A);
  answer = check_correct_matrix(B);
  if (answer == SUCCESS) {
    if (A->columns != B->rows) {
      answer = FAILURE;
    }
  }
  if (answer == SUCCESS) {
    if (!result) {
      answer = FAILURE;
    }
  }
  if (answer == SUCCESS) {
    answer = create_matrix(A->rows, B->columns, result);
  }
  if (answer == SUCCESS) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0.;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return answer;
}

void remove_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0 && A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
  }
}

