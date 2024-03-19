#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <systems.h>

#include "utils.h"

#define MAX_SIZE 1000

// Função para imprimir matriz
void printMatrix(real_t **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%f ", A[i][j]);
        printf("\n");
    }
}

//pivotização
void pivot(real_t **A, real_t *b, int n, int k)
{
    printf("Pivotização parcial\n");
    printMatrix(A, n);
    int p = k;
    real_t max = ABS(A[k][k]);
    for (int i = k + 1; i < n; i++)
    {
        if (ABS(A[i][k]) > max)
        {
            max = ABS(A[i][k]);
            p = i;
        }
    }
    if (p != k)
    {
        real_t *aux = A[k];
        A[k] = A[p];
        A[p] = aux;

        real_t aux2 = b[k];
        b[k] = b[p];
        b[p] = aux2;
    }
    printMatrix(A, n);
}

//linear systems solver with gauss elimination (pivot)
void gaussElimination(real_t **A, real_t *b, int n)
{
    int i, j, k;
    real_t factor;
    real_t *x = (real_t *)malloc(n * sizeof(real_t));

    for (i = 0; i < n; i++)
    {
        pivot(A, b, n, i);
        for (j = i + 1; j < n; j++)
        {
            factor = A[j][i] / A[i][i];
            for (k = i; k < n; k++)
            {
                A[j][k] = A[j][k] - factor * A[i][k];
            }
            b[j] = b[j] - factor * b[i];
        }
    }

    x[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        x[i] = b[i];
        for (j = i + 1; j < n; j++)
        {
            x[i] = x[i] - A[i][j] * x[j];
        }
        x[i] = x[i] / A[i][i];
    }

    printf("Solução do sistema:\n");
    for (i = 0; i < n; i++)
    {
        printf("x[%d] = %f\n", i, x[i]);
    }
    free(x);
}
