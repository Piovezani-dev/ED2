#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó da árvore
typedef struct No {
    int id;
    int curtidas;
    int comentarios;
    int total_interacoes;
    struct No *esquerda;
    struct No *direita;
} No;

// Função para criar um novo nó
No* criarNo(int id, int curtidas, int comentarios) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->id = id;
    novoNo->curtidas = curtidas;
    novoNo->comentarios = comentarios;
    novoNo->total_interacoes = curtidas + comentarios;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um novo usuário na árvore
No* inserirNo(No* raiz, int id, int curtidas, int comentarios) {
    if (raiz == NULL) return criarNo(id, curtidas, comentarios);

    int total_interacoes = curtidas + comentarios;
    if (total_interacoes > raiz->total_interacoes) {
        raiz->esquerda = inserirNo(raiz->esquerda, id, curtidas, comentarios);
    } else {
        raiz->direita = inserirNo(raiz->direita, id, curtidas, comentarios);
    }
    return raiz;
}

// Função para buscar o número de interações de um usuário específico pelo ID
No* buscarUsuario(No* raiz, int id) {
    if (raiz == NULL || raiz->id == id) return raiz;

    if (id < raiz->id) {
        return buscarUsuario(raiz->esquerda, id);
    } else {
        return buscarUsuario(raiz->direita, id);
    }
}

// Função para exibir usuários em ordem decrescente de interações (ordem reversa da árvore)
void exibirMaisEngajados(No* raiz) {
    if (raiz == NULL) return;
    exibirMaisEngajados(raiz->esquerda);
    printf("ID: %d, Curtidas: %d, Comentários: %d, Total de Interações: %d\n", raiz->id, raiz->curtidas, raiz->comentarios, raiz->total_interacoes);
    exibirMaisEngajados(raiz->direita);
}

// Função para encontrar o nó mais à direita (substituto do nó a ser removido)
No* encontrarMinimo(No* raiz) {
    while (raiz->direita != NULL) {
        raiz = raiz->direita;
    }
    return raiz;
}

// Função para remover um usuário
No* removerUsuario(No* raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->id) {
        raiz->esquerda = removerUsuario(raiz->esquerda, id);
    } else if (id > raiz->id) {
        raiz->direita = removerUsuario(raiz->direita, id);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No* temp = encontrarMinimo(raiz->esquerda);
        raiz->id = temp->id;
        raiz->curtidas = temp->curtidas;
        raiz->comentarios = temp->comentarios;
        raiz->total_interacoes = temp->total_interacoes;
        raiz->esquerda = removerUsuario(raiz->esquerda, temp->id);
    }
    return raiz;
}

// Função para atualizar as interações de um usuário
No* atualizarInteracoes(No* raiz, int id, int novasCurtidas, int novosComentarios) {
    No* usuario = buscarUsuario(raiz, id);
    if (usuario != NULL) {
        usuario->curtidas += novasCurtidas;
        usuario->comentarios += novosComentarios;
        usuario->total_interacoes = usuario->curtidas + usuario->comentarios;
        printf("Usuário ID %d atualizado. Novas curtidas: %d, Novos comentários: %d\n", usuario->id, usuario->curtidas, usuario->comentarios);
    } else {
        printf("Usuário ID %d não encontrado.\n", id);
    }
    return raiz;
}

// Função principal para testar a árvore
int main() {
    No* raiz = NULL;

    // Inserindo dados de exemplo
    raiz = inserirNo(raiz, 101, 50, 30);
    raiz = inserirNo(raiz, 102, 40, 10);
    raiz = inserirNo(raiz, 103, 60, 25);

    // Atualizando interações de um usuário
    raiz = atualizarInteracoes(raiz, 101, 10, 5);

    // Removendo um usuário
    raiz = removerUsuario(raiz, 102);

    // Exibindo usuários em ordem de engajamento
    printf("Usuários mais engajados:\n");
    exibirMaisEngajados(raiz);

    // Buscando um usuário específico
    No* usuario = buscarUsuario(raiz, 103);
    if (usuario != NULL) {
        printf("ID %d tem %d curtidas e %d comentários. Total de interações: %d\n", usuario->id, usuario->curtidas, usuario->comentarios, usuario->total_interacoes);
    } else {
        printf("Usuário não encontrado.\n");
    }

    return 0;
}
