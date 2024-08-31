//Gustavo Monteiro - 202201630

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //def de estrutura tipo nó, com ponteiro para o próximo e para o anterior
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* head = NULL;

void insertFront(int value) { //declarando o tipo que sera recebido
    printf("Insira um valor:\n");
    scanf("%d", &value);
    Node* newNode = (Node*)malloc(sizeof(Node)); //alocação de memória para um novo nó
    newNode->data = value; //data recebe o novo nó
    newNode->next = head; // muda o nó
    newNode->prev = NULL; // ponteiro anterior null, pois o novo nó é o primeiro
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

void deleteNode(Node* node) {
    if (node == head)
        head = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    free(node);
}

void printList() { 
    Node* temp = head; //começa pelo primeiro nó e percorre até o final, printando
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void search() {
    int value; //value que o usuario vai inserir
    printf("Digite o valor a ser buscado:\n");
    scanf("%d", &value);
    
    Node* temp = head; //começa pelo primeiro nó e percorre até encontrar o valor buscado
    while (temp != NULL) {
        if (temp->data == value) {
            printf("Valor %d encontrado na lista.\n", value);
            return; //se o valor foi encontrado, sai da função
        }
        temp = temp->next;
    }
    printf("Valor %d não encontrado na lista.\n", value); //se o valor não for encontrado
}

int main() {
    int value; //se não declarar aqui, não consigo rodar o código kkkk
    insertFront(value);
    insertFront(value);
    insertFront(value);
    printList();
    search(value);
    return 0;
}
