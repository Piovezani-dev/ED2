//Gustavo Monteiro - 202201630

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //estrutura do nó
    int data;            
    struct Node* next;    
} Node;


typedef struct Queue { //estrutura da fila
    Node* front;          
    Node* rear;           
} Queue;


Queue* createQueue() { //função de criar uma fila
    Queue* q = (Queue*)malloc(sizeof(Queue)); //alocação de memória
    if (q == NULL) {
        printf("Falha na alocação de memória para a fila.\n");
        return NULL;
    }
    q->front = q->rear = NULL; //inicializa a fila vazia
    return q;
}

void enqueue(Queue* q, int value) { //função de adicionar elemento na fila
    Node* newNode = (Node*)malloc(sizeof(Node)); //aloca memória para um novo nó
    if (newNode == NULL) {
        printf("Falha na alocação de memória para o novo nó.\n");
        return;
    }
    newNode->data = value; //define o valor do nó
    newNode->next = NULL; 
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) { //função para remover elementos
    if (q->front == NULL) { //verifica se a fila está vazia
        printf("Fila está vazia.\n");
        return -1; //retorna -1 para indicar que a fila está vazia
    }
    Node* temp = q->front; //armazena o nó do início da fila
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);  //libera a memória
    return data;
}

int isEmpty(Queue* q) { //função que verifica se a fila está vazia
    return q->front == NULL; //retorna 1 se a fila está vazia e 0 caso contrário
}

void printQueue(Queue* q) { //função para imprimir os elementos da fila
    if (isEmpty(q)) { //verifica se a fila está vazia
        printf("A fila está vazia.\n");
        return;
    }
    Node* temp = q->front;
    printf("Elementos da fila: ");
    while (temp != NULL) { //percorre toda a fila
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int countQueueElements(Queue* q) { //função para contar o número de elementos na fila
    int count = 0; 
    Node* temp = q->front;
    while (temp != NULL) { //percorre toda a fila
        count++;
        temp = temp->next;
    }
    return count; //retorna o número total de elementos
}

void clearQueue(Queue* q) { //função para limpar todos os elementos da fila
    while (!isEmpty(q)) { //enquanto a fila não estiver vazia
        dequeue(q);
    }
    free(q); //libera a memória da estrutura da fila
}

int main() {
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);

    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);

    enqueue(q, 40);
    enqueue(q, 50);
    printf("Número de elementos na fila: %d\n", countQueueElements(q));

    clearQueue(q);
    return 0;
}
