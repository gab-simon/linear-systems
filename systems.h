#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

#include "utils.h"

typedef struct {
  real_t *data;
} vector_t;

// functions

// gaussian elimination recebe uma matriz A e um vetor b e resolve o sistema Ax = b
void gaussian_elimination(real_t **A, real_t *b, int n);

// pivot recebe uma matriz A e um vetor b e um inteiro k e faz o pivoteamento parcial
void pivot(real_t **A, real_t *b, int n, int k);

// cc_dominant_diagonal recebe uma matriz A e um inteiro n e faz a matriz A ter diagonal dominante
void cc_dominant_diagonal(real_t **A, int n);

// cc_sassenfeld recebe uma matriz A e um inteiro n e faz a matriz A ter diagonal dominante
void cc_sassenfeld(real_t **A, int n);

// gauss_seidel recebe uma matriz A, um vetor b, um inteiro n, um real ε e um inteiro max_iter e resolve o sistema Ax = b
void gaussian_seidel(real_t **A, real_t *b, int n, real_t ε, int max_iter);

// euclidian_norm recebe dois vetores x e x_old e um inteiro n e retorna a norma euclidiana entre os vetores
real_t euclidian_norm(real_t *x, real_t *x_old, int n);

// print_matrix imprime a matriz A
void print_matrix(real_t **A, int n);

// residual_calc recebe uma matriz A, um vetor x, um vetor b e um inteiro n e retorna o resíduo do sistema
void print_result(real_t **A, real_t *x, real_t *b, int n);

// print_result_tridiagonal imprime o resultado do sistema tridiagonal
void print_result_tridiagonal(real_t *a, real_t *c, real_t *d, real_t *x, real_t *b, int n);

// max_value_vector recebe um vetor v, um inteiro n e um ponteiro para um real max e retorna o maior valor do vetor
real_t max_value_vector(real_t *v, int n, real_t *max);

// triagonal_gaussian_elimination recebe uma matriz A e um vetor b e resolve o sistema Ax = b
void tridiagonal_gaussian_elimination(real_t *a, real_t *c, real_t *d, real_t *b, int n);

// matrix_to_vector_diag recebe uma matriz A e um inteiro n e retorna o vetor diagonal
void matrix_to_vectors(real_t **A, vector_t *a, vector_t *c, vector_t *d, int n);

// is_tridiagonal recebe uma matriz A e um inteiro n e retorna se a matriz é tridiagonal
int is_tridiagonal(real_t **A, int n);

#endif // __SYSTEMS_H__