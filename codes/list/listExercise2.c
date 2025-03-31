#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct typeNode {
    char identifier;
    double tax;
    struct typeNode* next;
} typeNode;

typedef struct productNode {
    char name[20];
    char product_code[37];
    double value;
    typeNode* type;
    struct productNode* next;
} productNode;

void generate_uuid(char* uuid_str);
void insertNewType(typeNode** head, int position, char identifier, double tax);
void insertNewProduct(productNode** head, int position, char name[], char product_code[], double value, typeNode** type);
int findTypeNode(typeNode* head, typeNode* this);
double calculateByPrice(double value, double tax);
void searchProductByCode(productNode* head, char product_code[]);
int deleteTypeNode(typeNode** head, typeNode* typeToDelete, productNode* productList);
void displayMenu();
void clearInputBuffer();

int main() {
    typeNode* typeList = NULL;
    productNode* productList = NULL;
    
    int choice;
    char buffer[100];  

    do {
        displayMenu();
        printf("Escolha uma opção: ");
        
        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);
        
        switch (choice) {
            case 1: {
                char identifier;
                double tax;
                printf("Digite o identificador do tipo: ");
                scanf(" %c", &identifier);  
                clearInputBuffer(); 
                printf("Digite a taxa de imposto: ");
                scanf("%lf", &tax);
                clearInputBuffer();
                insertNewType(&typeList, 0, identifier, tax);
                break;
            }
            case 2: {
                // Inserir novo produto
                char name[20], product_code[37];
                double value;
                char typeIdentifier;
                printf("Digite o nome do produto: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  

                printf("Digite o código do produto: ");
                fgets(product_code, sizeof(product_code), stdin);
                product_code[strcspn(product_code, "\n")] = '\0';  

                printf("Digite o valor do produto: ");
                scanf("%lf", &value);
                clearInputBuffer(); 

                printf("Digite o identificador do tipo (A, B, etc.): ");
                scanf(" %c", &typeIdentifier);
                clearInputBuffer(); 

                typeNode* type = typeList;
                while (type != NULL && type->identifier != typeIdentifier) {
                    type = type->next;
                }
                
                if (type != NULL) {
                    insertNewProduct(&productList, 0, name, product_code, value, &type);
                } else {
                    printf("Tipo não encontrado!\n");
                }
                break;
            }
            case 3: {
                // Buscar produto por código
                char product_code[37];
                printf("Digite o código do produto a ser pesquisado: ");
                fgets(product_code, sizeof(product_code), stdin);
                product_code[strcspn(product_code, "\n")] = '\0'; 
                searchProductByCode(productList, product_code);
                break;
            }
            case 4: {
                char typeIdentifier;
                printf("Digite o identificador do tipo a ser excluído: ");
                scanf(" %c", &typeIdentifier);
                clearInputBuffer(); 

                typeNode* typeToDelete = typeList;
                while (typeToDelete != NULL && typeToDelete->identifier != typeIdentifier) {
                    typeToDelete = typeToDelete->next;
                }
                
                if (typeToDelete != NULL) {
                    deleteTypeNode(&typeList, typeToDelete, productList);
                } else {
                    printf("Tipo não encontrado!\n");
                }
                break;
            }
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (choice != 5); 

    return 0;
}

void insertNewType(typeNode** head, int position, char identifier, double tax) {
    typeNode* newNode = (typeNode*)malloc(sizeof(typeNode));
    newNode->identifier = identifier;
    newNode->tax = tax;
    newNode->next = NULL;

    if (position == 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    typeNode* current = *head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void insertNewProduct(productNode** head, int position, char name[], char product_code[], double value, typeNode** type) {
    if (!findTypeNode(*type, *type)) {
        printf("Tipo não definido!\n");
        return;
    }

    productNode* newNode = (productNode*)malloc(sizeof(productNode));
    strcpy(newNode->name, name);
    strcpy(newNode->product_code, product_code);
    newNode->value = value;
    newNode->type = *type;

    newNode->next = NULL;

    if (position == 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    productNode* current = *head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

int findTypeNode(typeNode* head, typeNode* this) {
    typeNode* current = head;
    while (current != NULL) {
        if (current == this) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

double calculateByPrice(double value, double tax) {
    return value + (value * tax / 100);
}

void searchProductByCode(productNode* head, char product_code[]) {
    productNode* current = head;
    
    while (current != NULL) {
        if (strcmp(current->product_code, product_code) == 0) {
            double finalPrice = calculateByPrice(current->value, current->type->tax);
            printf("Nome do Produto: %s\n", current->name);
            printf("Código do Produto: %s\n", current->product_code);
            printf("Preço Original: %.2f\n", current->value);
            printf("Imposto: %.2f%%\n", current->type->tax);
            printf("Preço Final com Imposto: %.2f\n", finalPrice);
            return;  
        }
        current = current->next;
    }
    printf("Produto com código %s não encontrado.\n", product_code);
}

int deleteTypeNode(typeNode** head, typeNode* typeToDelete, productNode* productList) {
    productNode* current = productList;
    while (current != NULL) {
        if (current->type == typeToDelete) {
            printf("Impossível excluir tipo '%c'! Existem produtos associados.\n", typeToDelete->identifier);
            return 0;
        }
        current = current->next;
    }

    typeNode* prev = NULL;
    current = *head;
    while (current != NULL) {
        if (current == typeToDelete) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);  
            printf("Tipo excluído com sucesso.\n");
            return 1; 
        }
        prev = current;
        current = current->next;
    }

    printf("Tipo não encontrado.\n");
    return 0; 
}

void displayMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Inserir novo tipo\n");
    printf("2. Inserir novo produto\n");
    printf("3. Buscar produto por código\n");
    printf("4. Excluir tipo\n");
    printf("5. Sair\n");
}

void clearInputBuffer() {
    while (getchar() != '\n');
}
