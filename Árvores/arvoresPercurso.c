#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int Id;
    int idade;
    struct Node* esquerda;  // left
    struct Node* direita;   // right
} Node;

// Função para criar um novo nó
Node* createNode(int Id, int idade) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->Id = Id;
    newNode->idade = idade;
    newNode->esquerda = NULL; // inicializa como NULL
    newNode->direita = NULL;  // inicializa como NULL
    return newNode;
}

// Função para inserir um nó na árvore usando a idade como critério
Node* insertNode(Node* root, int Id, int idade) {
    if (root == NULL) {
        return createNode(Id, idade);
    }
    
    if (idade < root->idade) {
        // Insere à esquerda se a idade é menor que a do nó atual
        root->esquerda = insertNode(root->esquerda, Id, idade);
    } else if (idade > root->idade) {
        // Insere à direita se a idade é maior que a do nó atual
        root->direita = insertNode(root->direita, Id, idade);
    } else {
        // Em caso de empate (mesma idade), podemos ignorar ou fazer uma reinserção
        printf("Idade %d já existe na árvore.\n", idade);
    }
    
    return root;
}

// Função para buscar um usuário pelo ID
Node* buscarID(Node* root, int Id) {
    if (root == NULL || root->Id == Id) {
        return root;
    }
    
    if (Id < root->Id) {
        return buscarID(root->esquerda, Id);
    } else {
        return buscarID(root->direita, Id);
    }
}

// Função para encontrar o menor nó (usado na remoção)
Node* minNode(Node* node) {
    Node* current = node;
    while (current && current->esquerda != NULL) {
        current = current->esquerda;
    }
    return current;
}

// Função para remover um usuário pelo ID
Node* deleteUser(Node* root, int Id) {
    if (root == NULL) {
        return root; // Caso base: árvore vazia ou usuário não encontrado
    }
    
    // A remoção ainda pode ser feita pelo ID, se necessário
    if (Id < root->Id) {
        root->esquerda = deleteUser(root->esquerda, Id);
    } else if (Id > root->Id) {
        root->direita = deleteUser(root->direita, Id);
    } else {
        // Achamos o nó a ser removido

        // Caso 1: Nó sem filhos (nó folha)
        if (root->esquerda == NULL && root->direita == NULL) {
            free(root);
            return NULL;
        }
        
        // Caso 2: Nó com apenas um filho
        else if (root->esquerda == NULL) { // Tem apenas filho direito
            Node* temp = root->direita;
            free(root);
            return temp;
        } else if (root->direita == NULL) { // Tem apenas filho esquerdo
            Node* temp = root->esquerda;
            free(root);
            return temp;
        }
        
        // Caso 3: Nó com dois filhos
        else {
            // Encontrando o sucessor em ordem (menor nó da subárvore direita)
            Node* temp = minNode(root->direita);
            
            // Copiando os dados do sucessor para o nó atual
            root->Id = temp->Id;
            root->idade = temp->idade;
            
            // Removendo o sucessor da subárvore direita
            root->direita = deleteUser(root->direita, temp->Id);
        }
    }
    return root;
}

// Função para exibir a árvore em ordem decrescente de idade
void exibirEmOrdem(Node* root) {
    if (root != NULL) {
        exibirEmOrdem(root->direita);   // Visita a subárvore direita (maior primeiro)
        printf("ID: %d, Idade: %d\n", root->Id, root->idade);  // Imprime o nó atual
        exibirEmOrdem(root->esquerda);  // Visita a subárvore esquerda
    }
}

// Função para exibir a árvore no percurso pré-ordem
void exibirPreOrdem(Node* root) {
    if (root != NULL) {
        printf("ID: %d, Idade: %d\n", root->Id, root->idade);  // Imprime o nó atual
        exibirPreOrdem(root->esquerda);  // Visita a subárvore esquerda
        exibirPreOrdem(root->direita);   // Visita a subárvore direita
    }
}

// Função para exibir a árvore no percurso pós-ordem
void exibirPosOrdem(Node* root) {
    if (root != NULL) {
        exibirPosOrdem(root->esquerda);  // Visita a subárvore esquerda
        exibirPosOrdem(root->direita);   // Visita a subárvore direita
        printf("ID: %d, Idade: %d\n", root->Id, root->idade);  // Imprime o nó atual
    }
}

// Função principal
int main() {
    Node* root = NULL;
    
    // Inserindo usuários
    root = insertNode(root, 101, 50);
    root = insertNode(root, 102, 40);
    root = insertNode(root, 103, 20);
    root = insertNode(root, 104, 30);
    root = insertNode(root, 105, 70);

    // Exibindo usuários em ordem decrescente de idade
    printf("Usuários em ordem decrescente de idade:\n");
    exibirEmOrdem(root);
    
    // Exibindo usuários em ordem decrescente de idade
    printf("\nUsuários em pre-ordem de idade:\n");
    exibirPreOrdem(root);
    
    // Exibindo usuários em ordem decrescente de idade
    printf("\nUsuários em pos-ordem de idade:\n");
    exibirPosOrdem(root);

    // Removendo um usuário
    root = deleteUser(root, 105);
    printf("\nApós remoção do usuário:\n");
    exibirEmOrdem(root);

    // Liberando memória
    void liberarArvore(Node* root) {
        if (root != NULL) {
            liberarArvore(root->esquerda);
            liberarArvore(root->direita);
            free(root);
        }
    }
    liberarArvore(root);

    return 0;
}
