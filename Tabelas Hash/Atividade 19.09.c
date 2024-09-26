#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10
#define VAZIO -1  // Indicador de posição vazia

typedef struct {
    int id;
    float valor;
    char local[50];
    char status[20];
    float tempo_preparo;
    float distancia;
    float tempo_pedido;
} Pedido;

typedef struct {
    Pedido *tabela[TAMANHO_HASH];
} TabelaHash;

int funcao_hash(int id) {
    return id % TAMANHO_HASH;
}

void inserir(TabelaHash *tabela, Pedido *pedido) {
    int indice = funcao_hash(pedido->id);
    int original_index = indice;

    while (tabela->tabela[indice] != NULL) {
        // Se o pedido já existe, pode-se decidir não inserir ou atualizar
        if (tabela->tabela[indice]->id == pedido->id) {
            printf("Pedido com ID %d já existe.\n", pedido->id);
            return;
        }
        // Avança para o próximo índice
        indice = (indice + 1) % TAMANHO_HASH;
        // Se voltar ao índice original, a tabela está cheia
        if (indice == original_index) {
            printf("Tabela hash cheia, não é possível inserir o pedido com ID %d.\n", pedido->id);
            return;
        }
    }

    tabela->tabela[indice] = pedido;  // Insere o pedido na posição vazia
}

Pedido *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int original_index = indice;

    while (tabela->tabela[indice] != NULL) {
        if (tabela->tabela[indice]->id == id) {
            return tabela->tabela[indice];
        }
        indice = (indice + 1) % TAMANHO_HASH;
        if (indice == original_index) {
            break;  // Voltou ao índice original, significa que o pedido não está na tabela
        }
    }
    return NULL;
}

void exibir_pedidos(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela->tabela[i] != NULL) {
            printf("Pedido ID: %d, Valor: %.2f, Local: %s, Status: %s, Tempo de Preparo: %.2f min, Distância: %.2f minutos, Tempo do Pedido: %.2f min\n",
                   tabela->tabela[i]->id,
                   tabela->tabela[i]->valor,
                   tabela->tabela[i]->local,
                   tabela->tabela[i]->status,
                   tabela->tabela[i]->tempo_preparo,
                   tabela->tabela[i]->distancia,
                   tabela->tabela[i]->tempo_pedido);
        }
    }
}

void liberar_tabela(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        free(tabela->tabela[i]);  // Libera cada pedido alocado
    }
}

int main() {
    TabelaHash tabela = {NULL};

    // Criação de alguns pedidos
    Pedido *pedido1 = (Pedido *)malloc(sizeof(Pedido));
    *pedido1 = (Pedido){101, 100.50, "São Paulo", "pedido feito", 30.0, 15.0, 45.0};
   
    Pedido *pedido2 = (Pedido *)malloc(sizeof(Pedido));
    *pedido2 = (Pedido){102, 25.75, "Rio de Janeiro", "entregue", 15.0, 5.0, 20.0};
   
    Pedido *pedido3 = (Pedido *)malloc(sizeof(Pedido));
    *pedido3 = (Pedido){103, 150.00, "Miami", "cancelado", 40.0, 20.0, 60.0};

    // Insere os pedidos na tabela hash
    inserir(&tabela, pedido1);
    inserir(&tabela, pedido2);
    inserir(&tabela, pedido3);

    // Busca por um pedido específico
    Pedido *p = buscar(&tabela, 105);
    if (p != NULL) {
        printf("Pedido encontrado: ID: %d, Valor: %.2f, Local: %s, Status: %s, Tempo de Preparo: %.2f min, Distância: %.2f minutos, Tempo do Pedido: %.2f min\n",
               p->id, p->valor, p->local, p->status, p->tempo_preparo, p->distancia, p->tempo_pedido);
    } else {
        printf("Pedido não encontrado.\n");
    }

    // Exibir todos os pedidos
    printf("\nTodos os pedidos:\n");
    exibir_pedidos(&tabela);

    // Liberar a tabela hash
    liberar_tabela(&tabela);

    return 0;
}
