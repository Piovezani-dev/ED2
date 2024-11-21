#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da árvore AVL
struct Node {
    int id;               // ID do cliente (chave de busca)
    char name[50];        // Nome do cliente
    struct Node *left;
    struct Node *right;
    int height;
};

// Função para criar um novo nó
struct Node* newNode(int id, char name[]) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->id = id;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // novo nó é inicialmente uma folha
    return node;
}

// Função para obter a altura de um nó
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação à direita
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Obter o fator de balanceamento do nó
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int id, char name[]) {
    if (node == NULL)
        return newNode(id, name);

    // Comparação com o ID do nó para decidir a posição na árvore
    if (id < node->id)
        node->left = insert(node->left, id, name);
    else if (id > node->id)
        node->right = insert(node->right, id, name);
    else  // IDs duplicados não são permitidos na árvore AVL
        return node;

    // Atualizar altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Obter fator de balanceamento
    int balance = getBalance(node);

    // Casos de rotação para balanceamento
    // Caso Esquerda-Esquerda
    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para exibir a árvore AVL em ordem
void inOrder(struct Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("ID: %d, Nome: %s\n", root->id, root->name);
        inOrder(root->right);
    }
}

// Função para encontrar o nó com o valor mínimo (para substituição)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função para remover um nó na árvore AVL
struct Node* deleteNode(struct Node* root, int id) {
    // Passo 1: Realizar a remoção como em uma árvore binária de pesquisa normal
    if (root == NULL)
        return root;

    // Se o id a ser removido for menor que a chave do nó, ele está na subárvore esquerda
    if (id < root->id)
        root->left = deleteNode(root->left, id);

    // Se o id a ser removido for maior que a chave do nó, ele está na subárvore direita
    else if (id > root->id)
        root->right = deleteNode(root->right, id);

    // Caso 1: O nó a ser removido é uma folha (não tem filhos)
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Caso 2: O nó a ser removido tem um único filho
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Caso 3: O nó a ser removido tem dois filhos
        else {
            struct Node* temp = minValueNode(root->right);  // Sucessor in-order
            root->id = temp->id;
            strcpy(root->name, temp->name);
            root->right = deleteNode(root->right, temp->id);  // Remover o sucessor in-order
        }
    }

    // Passo 2: Atualizar a altura do nó atual
    root->height = 1 + max(height(root->left), height(root->right));

    // Passo 3: Obter o fator de balanceamento
    int balance = getBalance(root);

    // Passo 4: Rebalancear a árvore, se necessário

    // Caso Esquerda-Esquerda
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Caso Direita-Direita
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Caso Esquerda-Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Retornar o nó (possivelmente reequilibrado)
    return root;
}

// Função para exibir a árvore AVL em pré-ordem (estrutura da árvore)
void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("ID: %d, Nome: %s\n", root->id, root->name);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Função para buscar um cliente por ID
struct Node* search(struct Node* root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);

    return search(root->right, id);
}

// Função para realizar consultas e mostrar reorganização
void searchAndShowReorganization(struct Node* root, int id) {
    printf("Buscando cliente com ID: %d...\n", id);
    struct Node* result = search(root, id);

    if (result) {
        printf("Cliente encontrado: ID: %d, Nome: %s\n", result->id, result->name);
    } else {
        printf("Cliente com ID %d não encontrado.\n", id);
    }

    printf("Estrutura da árvore após consulta (pré-ordem):\n");
    preOrder(root);
}

// Função principal
int main() {
    struct Node *root = NULL;

    // Inserção de nós como exemplo
    root = insert(root, 10, "Alice");
    root = insert(root, 70, "Grace");
    root = insert(root, 20, "Bob");
    root = insert(root, 50, "Eve");
    root = insert(root, 30, "Charlie");
    root = insert(root, 40, "Diana");
    root = insert(root, 60, "Frank");

    root = deleteNode(root, 50);

    printf("Árvore AVL em ordem:\n");
    inOrder(root);

    printf("\n--- Consultas ---\n");
    searchAndShowReorganization(root, 20);
    searchAndShowReorganization(root, 50); // Testando cliente removido
    searchAndShowReorganization(root, 60);

    return 0;
}
