#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* right;
    struct Node* left;
    int depth;
} Node;

#define SPACE_STEP 5

Node* createNode(int data, int depth);
void insert(Node** root, int value, int depth);
Node* binarySearch(Node* root, int value);
Node* getSuccessor(Node* curr);
Node* deleteNode(Node* root, int value);
void printTreeInOrder(Node* root);
void printTreeVisual(Node* root, int space);
void updateDepth(Node* root, int currentDepth);
void freeTree(Node* root);

int main() {
    Node* root = NULL;

    insert(&root, 50, 0);
    insert(&root, 30, 0);
    insert(&root, 70, 0);
    insert(&root, 20, 0);
    insert(&root, 40, 0);
    insert(&root, 60, 0);
    insert(&root, 80, 0);

    printf("\n=== Impressão em ordem (in-order): ===\n");
    printTreeInOrder(root);

    printf("\n=== Impressão visual da árvore: ===\n");
    printTreeVisual(root, 0);

    root = deleteNode(root, 60);
    updateDepth(root, 0);

    root = deleteNode(root, 30);
    updateDepth(root, 0);

    printf("\n=== Após remoções ===\n");

    printf("\n=== Impressão em ordem (in-order): ===\n");
    printTreeInOrder(root);

    printf("\n=== Impressão visual da árvore: ===\n");
    printTreeVisual(root, 0);

    freeTree(root);

    return 0;
}

Node* createNode(int data, int depth){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->depth = depth;
    return newNode;
}

void insert(Node** root, int value, int depth){
    if (*root == NULL) {
        *root = createNode(value, depth);
        return;
    }

    if (value < (*root)->data) {
        insert(&((*root)->left), value, depth + 1);
    } else if (value > (*root)->data) {
        insert(&((*root)->right), value, depth + 1);
    }
}

Node* binarySearch(Node* root, int value){
    if (root == NULL) return NULL;
    if (root->data == value) return root;

    if (value < root->data)
        return binarySearch(root->left, value);
    else
        return binarySearch(root->right, value);
}

Node* getSuccessor(Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* succ = getSuccessor(root);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}

void printTreeInOrder(Node* root) {
    if (root == NULL) return;

    printTreeInOrder(root->left);
    printf("Valor: %d (Profundidade: %d)\n", root->data, root->depth);
    printTreeInOrder(root->right);
}

void printTreeVisual(Node* root, int space) {
    if (root == NULL)
        return;

    space += SPACE_STEP;

    printTreeVisual(root->right, space);

    printf("\n");
    for (int i = SPACE_STEP; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    printTreeVisual(root->left, space);
}

void updateDepth(Node* root, int currentDepth) {
    if (root == NULL) return;

    root->depth = currentDepth;
    updateDepth(root->left, currentDepth + 1);
    updateDepth(root->right, currentDepth + 1);
}

void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
