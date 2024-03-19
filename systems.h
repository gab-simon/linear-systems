#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

#include "utils.h"

// functions
// gaussian elimination recebe uma matriz A e um vetor b e resolve o sistema Ax = b
void gaussian_elimination(real_t **A, real_t *b, int n);

void pivot(real_t **A, real_t *b, int n, int k);

void printMatrix(real_t **A, int n);

#endif // __SYSTEMS_H__