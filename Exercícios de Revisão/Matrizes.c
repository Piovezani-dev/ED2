//Gustavo Monteiro - 202201630

#include <stdio.h>

int main() {
    printf("Digite um número que será o número de colunas e linhas:\n");
    int n;
    scanf("%d", &n);
    int matriz[n][n];
    int i, j, soma = 0;

    printf("Insira os elementos da matriz 3x3:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]);
            if (i == j) {
                soma += matriz[i][j];
            }
        }
    }

    printf("Soma dos elementos da diagonal principal: %d\n", soma);
    return 0;
}
