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
void print_matrix(real_t **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%le ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

//pivotização parcial
void pivot(real_t **A, real_t *b, int n, int k)
{
    int i, max;
    real_t temp;
    real_t *tempRow = (real_t *)malloc(n * sizeof(real_t));
    
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
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    x[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        x[i] = b[i];
        for (j = i + 1; j < n; j++)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    print_result(A, x, b, n);

    free(x);
}

// Função para fazer a matriz A ter diagonal dominante
void cc_dominant_diagonal(real_t **A, int n)
{
    int i, j;
    real_t sum;

    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++)
        {
            if (i != j)
                sum += ABS(A[i][j]);
        }
        A[i][i] = sum + 1;
    }
}

// Função para fazer a matriz A ter diagonal dominante
void cc_sassenfeld(real_t **A, int n)
{
    int i, j;
    real_t sum;
    real_t *beta = (real_t *)malloc(n * sizeof(real_t));

    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++)
        {
            if (i != j)
                sum += ABS(A[i][j]);
        }
        beta[i] = sum / ABS(A[i][i]);
    }

    real_t max = beta[0];
    for (i = 1; i < n; i++)
    {
        if (beta[i] > max)
            max = beta[i];
    }
    free(beta);
}

real_t euclidian_norm(real_t *x, real_t *x_old, int n)
{
    int i;
    real_t sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += (x[i] - x_old[i]) * (x[i] - x_old[i]);
    }
    return sqrt(sum);
}

real_t max_value_vector(real_t *v, int n, real_t *max)
{
    int i;
    *max = v[0];
    for (i = 1; i < n; i++)
    {
        if (v[i] > *max)
            *max = v[i];
    }

    return *max;
}

// gauss seidel
void gaussian_seidel(real_t **A, real_t *b, int n, real_t ε, int max_iter)
{
    int i, j, k;

    real_t sum;

    real_t sums[n];

    real_t *x = (real_t *)malloc(n * sizeof(real_t));
    real_t *x_old = (real_t *)malloc(n * sizeof(real_t));

    for (i = 0; i < n; i++)
    {
        x[i] = 0;
    }

    for (k = 0; k < max_iter; k++)
    {
        for (i = 0; i < n; i++)
        {
            x_old[i] = x[i];
        }

        for (i = 0; i < n; i++)
        {
            sum = 0;
            for (j = 0; j < n; j++)
            {
                if (j != i)
                    sum +=A[i][j] * x[j]; 
            }
            x[i] = (b[i] - sum) / A[i][i];
            sums[i] = (ABS(x[i] - x_old[i]));
        }

        if (max_value_vector(sums, n, &sum) < ε)
        {
            return print_result(A, x, b, n);
        }

    }
    free(x);
    free(x_old);
}

void matrix_to_vectors(real_t **A, vector_t *a, vector_t *c, vector_t *d, int n)
{
    a->data = (real_t *)malloc((n-1) * sizeof(real_t));
    c->data = (real_t *)malloc((n-1) * sizeof(real_t));
    d->data = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; i++)
    {
        d->data[i] = A[i][i];
        if (i < n - 1)
            c->data[i] = A[i][i + 1];
        if (i > 0)
            a->data[i] = A[i][i - 1];
    }
}

void tridiagonal_gaussian_elimination(real_t *a, real_t *c, real_t *d, real_t *b,  int n)
{
    real_t *x = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 1; i < n; i++)
    {
        real_t factor = a[i] / d[i];
        a[i + 1] -= factor * c[i];
        b[i + 1] -= factor * b[i];
    }

    x[n - 1] = b[n - 1] / d[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        x[i] = (b[i] - c[i] * x[i + 1]) / d[i];
    }

    print_result_tridiagonal(a, c, d, x, b, n);

    free(x);
}

void tridiagonal_gaussian_seidel(real_t *a, real_t *c, real_t *d, real_t *b, int n, real_t ε, int max_iter)
{
    int i, k;
    real_t sum;
    real_t *x = (real_t *)malloc(n * sizeof(real_t));
    real_t *x_old = (real_t *)malloc(n * sizeof(real_t));
    real_t *sums = (real_t *)malloc(n * sizeof(real_t));

    for (i = 0; i < n; i++)
    {
        x[i] = 0;
    }

    for (k = 0; k < max_iter; k++)
    {
        for (i = 0; i < n; i++)
        {
            x_old[i] = x[i];
        }

        for (i = 0; i < n; i++)
        {
            sum = 0;
            if (i > 0)
                sum += a[i] * x[i - 1];
            if (i < n - 1)
                sum += c[i] * x[i + 1];
            x[i] = (b[i] - sum) / d[i];
            sums[i] = ABS(x[i] - x_old[i]);
        }

        if (max_value_vector(sums, n, &sum) < ε)
            return print_result_tridiagonal(a, c, d, x, b, n);
    }

    free(x);
    free(x_old);
    free(sums);
}

void print_result_tridiagonal(real_t *a, real_t *c, real_t *d, real_t *x, real_t *b, int n)
{
    real_t *r = (real_t *)malloc(n * sizeof(real_t));

    printf("Solução do sistema:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x[%d] = %.12f\n", i, x[i]);
    }

    printf("Resíduo do sistema:\n");
    for (int i = 0; i < n; i++)
    {
        r[i] = b[i];
        r[i] -= a[i] * x[i - 1] + d[i] * x[i] + c[i] * x[i + 1];
        printf("r[%d] = %.12f\n", i, ABS(r[i]));
    }

    free(r);
}

void print_result(real_t **A, real_t *x, real_t *b, int n)
{
    real_t *r = (real_t *)malloc(n * sizeof(real_t));

    printf("Solução do sistema:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x[%d] = %.12f\n", i, x[i]);
    }

    printf("Resíduo do sistema:\n");
    for (int i = 0; i < n; i++)
    {
        r[i] = b[i];
        for (int j = 0; j < n; j++)
        {
            r[i] -= A[i][j] * x[j];
        }
        printf("r[%d] = %.12f\n", i, ABS(r[i]));
    }

    free(r);
}

