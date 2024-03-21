#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "systems.h"
#include "utils.h"

int main( int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    real_t **matriz = malloc(n * sizeof(real_t));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc((n + 1) * sizeof(real_t));
    }

    // Lê os elementos da matriz, incluindo a coluna extra (vetor b)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            scanf("%le", &matriz[i][j]);
        }
    }

    real_t vetorB[n];
    for (int i = 0; i < n; i++) {
        vetorB[i] = matriz[i][n];
    }

    gaussian_elimination(matriz, vetorB, n);
    gaussian_seidel(matriz, vetorB, n, 0.0001, 1000);

    if(is_tridiagonal(matriz, n)){
        real_t a[n];
        real_t c[n];
        real_t d[n];
        matrix_to_vectors(matriz, a, c, d, n);

        for (int i = 0; i < n; i++) {
            printf("a[%d] = %f\n", i, a[i]);
        }
        tridiagonal_gaussian_elimination(a, vetorB, c, d, n);
    } else {
        printf("A matriz não é tridiagonal\n");
    }

    return 0;
}