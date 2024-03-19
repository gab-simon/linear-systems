#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "systems.h"
#include "utils.h"

#define MAX_SIZE 1000

// Função para imprimir matriz
void printMatrix(real_t **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%le ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

//pivotização total
void pivot(real_t **A, real_t *b, int n, int k)
{
    int i, max;
    real_t temp;
    real_t *tempRow = (real_t *)malloc(n * sizeof(real_t));
    
    printMatrix(A, n);

    max = k;
    for (i = k + 1; i < n; i++)
    {
        if (ABS(A[i][k]) > ABS(A[max][k]))
            max = i;
    }

    if (max != k)
    {
        tempRow = A[k];
        A[k] = A[max];
        A[max] = tempRow;

        temp = b[k];
        b[k] = b[max];
        b[max] = temp;
    }

    printMatrix(A, n);
}

//linear systems solver with gauss elimination (pivot)
void gaussian_elimination(real_t **A, real_t *b, int n)
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
