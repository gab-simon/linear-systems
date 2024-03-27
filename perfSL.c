#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "systems.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);

    // Aloca a matriz
    real_t **matrix = malloc(n * sizeof(real_t));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc((n + 1) * sizeof(real_t));
    }

    // Lê os elementos da matriz, incluindo a coluna extra (vetor b)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            scanf("%le", &matrix[i][j]);
        }
    }

    // Cria um vetor b a partir da última coluna da matriz
    real_t vector_b[n];
    for (int i = 0; i < n; i++) {
        vector_b[i] = matrix[i][n];
    }
    //calcula o tempo de execução
    rtime_t temp_GL = timestamp();
    gaussian_elimination(matrix, vector_b, n);
    printf("Tempo de execução do método de eliminação de gauss: %f\n\n", timestamp() - temp_GL);

    // calcula tempo
    rtime_t temp_GS = timestamp();
    gaussian_seidel(matrix, vector_b, n, 0.0001, 1000);
    printf("Tempo de execução do método de gauss-seidel: %f\n\n", timestamp() - temp_GS);

    // Cria vetores para a matriz tridiagonal
    vector_t *vector_a = malloc(n * sizeof(vector_t));
    vector_t *vector_c = malloc(n * sizeof(vector_t));
    vector_t *vector_d = malloc(n + 1 * sizeof(vector_t));

    // Converte a matriz para vetores
    matrix_to_vectors(matrix, vector_a, vector_c, vector_d, n);

    // Calcula o tempo de execução
    rtime_t temp_TGE = timestamp();
    tridiagonal_gaussian_elimination(vector_a->data, vector_c->data, vector_d->data, vector_b, n);
    printf("Tempo de execução do método de eliminação de gauss tridiagonal: %f\n\n", timestamp() - temp_TGE);

    // Calcula o tempo de execução
    rtime_t temp_TGS = timestamp();
    tridiagonal_gaussian_seidel(vector_a->data, vector_c->data, vector_d->data, vector_b, n, 0.0001, 1000);
    printf("Tempo de execução do método de gauss-seidel tridiagonal: %f\n\n", timestamp() - temp_TGS);

    return 0;
}