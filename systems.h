#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

#include "utils.h"

// functions

// gaussian elimination recebe uma matriz A e um vetor b e resolve o sistema Ax = b
void gaussian_elimination(real_t **A, real_t *b, int n);

// pivot recebe uma matriz A e um vetor b e um inteiro k e faz o pivoteamento parcial
void pivot(real_t **A, real_t *b, int n, int k);

// cc_dominant_diagonal recebe uma matriz A e um inteiro n e faz a matriz A ter diagonal dominante
void cc_dominant_diagonal(real_t **A, int n);

// cc_sassenfeld recebe uma matriz A e um inteiro n e faz a matriz A ter diagonal dominante
void cc_sassenfeld(real_t **A, int n);

// gauss_seidel recebe uma matriz A, um vetor b, um inteiro n, um real tol e um inteiro max_iter e resolve o sistema Ax = b
void gaussian_seidel(real_t **A, real_t *b, int n, real_t tol, int max_iter);

// euclidian_norm recebe dois vetores x e x_old e um inteiro n e retorna a norma euclidiana entre os vetores
real_t euclidian_norm(real_t *x, real_t *x_old, int n);

// print_matrix imprime a matriz A
void print_matrix(real_t **A, int n);

#endif // __SYSTEMS_H__