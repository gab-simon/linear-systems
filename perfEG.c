#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <systems.h>
#include <utils.h>

int main( int argc, char *argv[])
{
    // primeiro recebe um n tamanho da matriz, por exemplo 4
    // segundo recebe a matriz de tamanho n*n

    // exemplo de entrada:
    // 4
    // 1 2 3 4 5
    // 5 6 7 8 5
    // 9 10 11 12 5
    // 13 14 15 16 5
    // 5 5 5 5 sao o vetor b

    int n;
    scanf("%d", &n);

    real_t matriz[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    real_t vetorB[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &matriz[i][n]);
        printf("%d\n", matriz[i][n]);
    }
    gaussElimination(matriz, n);

    return 0;
}