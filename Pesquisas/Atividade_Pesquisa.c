#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 100000  // Número de produtos
#define MAX_NAME_LENGTH 50 // Tamanho máximo do nome do produto

typedef struct {
    int id;                  // ID único do produto
    char name[MAX_NAME_LENGTH];  // Nome do produto
    float price;             // Preço do produto
} Product;

const char *productNames[] = {
    "Smartphone Samsung Galaxy",
    "Notebook Dell Inspiron",
    "Geladeira Brastemp Frost Free",
    "Cafeteira Nespresso",
    "Fritadeira Airfryer Mondial",
    "TV LED 50 Polegadas LG",
    "Console Playstation 5",
    "Headset Gamer HyperX",
    "Máquina de Lavar Electrolux",
    "Ventilador Arno Turbo",
    "Teclado Mecânico Razer",
    "Impressora Multifuncional HP",
    "Relógio Smartwatch Apple",
    "Câmera DSLR Canon",
    "Micro-ondas Panasonic",
    "Bicicleta Caloi Aro 29",
    "Perfume Chanel No 5",
    "Sapato Social Masculino",
    "Bolsa Feminina de Couro",
    "Óculos de Sol Ray-Ban"
};

void generateProductName(char *name) {
    int index = rand() % (sizeof(productNames) / sizeof(productNames[0]));
    strncpy(name, productNames[index], MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0';
}

void generateProductList(Product products[], int numProducts) {
    for (int i = 0; i < numProducts; ++i) {
        products[i].id = i + 1; // ID sequencial
        generateProductName(products[i].name); // Nome aleatório
        products[i].price = (rand() % 10000) / 100.0; // Preço aleatório entre $0 e $100
    }
}

void printProduct(Product product) {
    printf("ID: %d, Nome: %s, Preço: $%.2f\n", product.id, product.name, product.price);
}

void printProductList(Product products[], int numProducts) {
    printf("\nLista de produtos gerados:\n");
    for (int i = 0; i < numProducts; ++i) {
        printProduct(products[i]);
    }
}

// Função para busca sequencial por ID
int sequentialSearch(Product products[], int numProducts, int targetId) {
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == targetId) {
            return i; // Retorna o índice se o ID for encontrado
        }
    }
    return -1; // Produto não encontrado
}

// Função para busca binária por ID
int binarySearch(Product products[], int low, int high, int targetId) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (products[mid].id == targetId) {
            return mid; // Produto encontrado
        }
        if (products[mid].id < targetId) {
            low = mid + 1; // O alvo está na metade superior
        } else {
            high = mid - 1; // O alvo está na metade inferior
        }
    }
    return -1; // Produto não encontrado
}

int compare(const void* a, const void* b) {
    Product* productA = (Product*)a;
    Product* productB = (Product*)b;
    return productA->id - productB->id; // Comparação pelo ID
}

// Função principal
int main() {
    srand(time(NULL));

    Product products[MAX_PRODUCTS];
    int numProducts = MAX_PRODUCTS;

    generateProductList(products, numProducts);
    printProductList(products, 15); // Exibe apenas os 15 primeiros produtos

    // Define o ID alvo para busca
    int targetId = MAX_PRODUCTS-1; // Exemplo: busca pelo produto com ID 5

    // Busca sequencial por ID
    printf("\nBusca sequencial pelo ID %d:\n", targetId);
    clock_t startSeq = clock(); // Tempo de início
    int seqResult = sequentialSearch(products, numProducts, targetId);
    clock_t endSeq = clock(); // Tempo de fim

    if (seqResult != -1) {
        printf("Produto encontrado na posição %d:\n", seqResult);
        printProduct(products[seqResult]);
    } else {
        printf("Produto não encontrado na busca sequencial.\n");
    }

    double timeSeq = (double)(endSeq - startSeq) / CLOCKS_PER_SEC; // Tempo em segundos
    printf("Tempo de execução da busca sequencial: %.6f segundos\n", timeSeq);

    // Ordenar a lista de produtos por ID
    qsort(products, numProducts, sizeof(Product), compare);

    // Busca binária por ID
    printf("\nBusca binária pelo ID %d:\n", targetId);
    clock_t startBin = clock(); // Tempo de início
    int binResult = binarySearch(products, 0, numProducts - 1, targetId);
    clock_t endBin = clock(); // Tempo de fim

    if (binResult != -1) {
        printf("Produto encontrado na posição %d:\n", binResult);
        printProduct(products[binResult]);
    } else {
        printf("Produto não encontrado na busca binária.\n");
    }

    double timeBin = (double)(endBin - startBin) / CLOCKS_PER_SEC; // Tempo em segundos
    printf("Tempo de execução da busca binária: %.6f segundos\n", timeBin);

    return 0;
}
