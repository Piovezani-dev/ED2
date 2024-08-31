//Gustavo Monteiro - 202201630

#include <stdio.h>

int main() {
    int n;
    int i, temp;

    printf("Insira a quatidade de elementos do vetor?\n"); /*Pedido para o usuario
    acrescentar uma quantidade de elementos (poderia ter sido rand)*/
    scanf("%i", &n); //Escaneia a quantidade de elementos
    
    int vetor[n]; //iniciado apos receber n
    
    for (i = 0; i < n; i++){ //for que cria os elementos de vetor[n] em ordem
        vetor[i] = i;
    }

    for (i = 0; i < n/2; i++) { //5 era metade entao ficou n/2
        temp = vetor[i];
        vetor[i] = vetor[(n - 1) - i]; //9 era o ultimo, entao ficou n-1
        vetor[(n - 1) - i] = temp;
    }

    printf("Vetor invertido:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}
