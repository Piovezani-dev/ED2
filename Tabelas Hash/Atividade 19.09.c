#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar um pedido de delivery
typedef struct {
    int id;                // ID único do pedido
    float valor;           // Valor do pedido
    char local[50];        // Local de entrega
    char status[20];       // Status: "pedido feito", "entregue", "cancelado"
    float tempo_preparo;   // Tempo de preparo em minutos
    float distancia;       // Distância da entrega em minutos
    float tempo_pedido;    // Tempo total do pedido em minutos
} Pedido;

// Estrutura da Tabela Hash
typedef struct {
    Pedido *tabela[TAMANHO_HASH];  // Array de ponteiros para armazenar pedidos
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID do pedido
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para inserir um pedido na tabela hash
void inserir(TabelaHash *tabela, Pedido *pedido) {
    int indice = funcao_hash(pedido->id);  // Calcula o índice baseado no ID
    tabela->tabela[indice] = pedido;  // Insere o pedido na tabela
}

// Função para buscar um pedido na tabela hash pelo ID
Pedido *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para busca
    return tabela->tabela[indice];  // Retorna o pedido encontrado
}

// Função para exibir todos os pedidos
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

// Função principal para demonstrar o uso da tabela hash com pedidos de delivery
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Criação de alguns pedidos
    Pedido pedido1 = {101, 100.50, "São Paulo", "pedido feito", 30.0, 15.0, 45.0};
    Pedido pedido2 = {102, 25.75, "Rio de Janeiro", "entregue", 15.0, 5.0, 20.0};
    Pedido pedido3 = {103, 150.00, "Miami", "cancelado", 40.0, 20.0, 60.0};

    // Insere os pedidos na tabela hash
    inserir(&tabela, &pedido1);
    inserir(&tabela, &pedido2);
    inserir(&tabela, &pedido3);

    // Busca por um pedido específico
    Pedido *p = buscar(&tabela, 105);
    if (p != NULL) {
        printf("Pedido encontrado: ID: %d, Valor: %.2f, Local: %s, Status: %s, Tempo de Preparo: %.2f min, Distância: %.2f km, Tempo do Pedido: %.2f min\n",
               p->id, p->valor, p->local, p->status, p->tempo_preparo, p->distancia, p->tempo_pedido);
    } else {
        printf("Pedido não encontrado.\n");
    }

    // Exibir todos os pedidos
    printf("\nTodos os pedidos:\n");
    exibir_pedidos(&tabela);

    return 0;
}
