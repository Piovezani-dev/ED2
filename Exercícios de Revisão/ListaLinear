//Gustavo Monteiro - 202201630

#include <stdio.h>
#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;

void buscar(int elemento){
    int i;
    int aux = 0;
    for(i = 0; i < MAX_SIZE; i++){
        if (lista[i] == elemento){
            printf("Seu elemento (elemento: %i) esta na posição:\n%i\n", elemento, i);
            aux++;
        }    
    }
    if (aux==0) printf("Seu elemento (elemento: %i) não foi encontrado.\n", elemento);
}

void inserir(int elemento) {
    if (tamanho < MAX_SIZE) {
        lista[tamanho++] = elemento;
    } else {
        printf("Lista cheia!\n");
    }
}

void remover(int index) {
    if (index < 0 || index >= tamanho) {
        printf("Índice inválido!\n");
    } else {
        for (int i = index; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1];
        }
        tamanho--;
    }
}

void imprimir() {
    printf("Elementos da lista:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

int main() {
    inserir(10);
    inserir(20);
    inserir(30);
    imprimir();
    buscar(30);
    remover(1);
    buscar(20); //buscando elemento removido
    imprimir();
    return 0;
}
