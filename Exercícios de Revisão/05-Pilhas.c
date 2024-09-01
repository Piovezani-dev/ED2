
//Gustavo Monteiro - 202201630

#include <stdio.h>
#define MAX_SIZE 3

int pilha[MAX_SIZE];
int topo = -1;

/*proposta de expansão: para fazer uma função que pudesse fazer uma expansão dinâmica deveríamos
alterar a estrutura da pilha, partindo a utilizar ponteiros e alocação dinâmica para
expandi-la quando necessário.
Caso não houver a necessidade de ter uma #define MAX_SIZE 3, poderíamos também declarar
de forma dinâmica "n" na main ou criando um tipo de estrutura pilha (mas fugiria do
proposto peloo exercício)
*/

void push(int elemento) { //função para adicionar elementos na pilha
    if (topo < MAX_SIZE - 1) { //verifica se há espaço e adiciona no topo, se não tiver ele informa!
        pilha[++topo] = elemento;
    } else {
        printf("Pilha cheia!\n");
    }
}

int pop() { //remove elemento e retorna outro elemento para o topo
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo--];
    }
}

void vazio(){ //função para verificar se está vazia
    if (topo == -1) { //verifica o o topo, se for -1 significa que não há elementos na pilha
        printf("A pilha está vazia!\n");
    } else printf("A pilha não está vazia!\n"); //informa caso a fila não esteja vazia
}

int top() { //função que retorna o elemento do topo, mas sem removê-lo
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo];
    }
}

void imprimir() { //percorre de cima para baixo a pilha e imprime os elementos
    printf("Conteúdo da pilha:\n");
    for (int i = topo; i >= 0; i--) {
        printf("%d ", pilha[i]);
    }
    printf("\n");
}

int main() {
    push(10); //inserindo 10 e abaixo 20 e 30
    push(20);
    push(30);
    push(40); //tenta inserir o 40 e recebe que a pilha está cheia
    imprimir(); 
    printf("Elemento no topo: %d\n", top()); //verifica qual o elemento do topo
    printf("Elemento removido: %d\n", pop()); //remove o elemento do topo
    imprimir();
    vazio(); //verificação se está vazia
    return 0;
}
