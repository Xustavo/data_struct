#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct stack {
    int items[MAX];
    int top;
} stack;

void createEmptyStack(stack *s);
int isEmpty(stack *s);
int isFull(stack *s);
void push(stack *s, int value);
void pop(stack *s);
void peek(stack *s);
void showFullStack(stack *s);

int main() {
    stack s;
    int choice, value;

    createEmptyStack(&s);

    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Empilhar (Push)\n");
        printf("2. Desempilhar (Pop)\n");
        printf("3. Ver topo (Peek)\n");
        printf("4. Exibir pilha\n");
        printf("5. Sair\n");
        printf("Opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o valor a ser empilhado: ");
                scanf("%d", &value);
                push(&s, value);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                peek(&s);
                break;
            case 4:
                showFullStack(&s);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 5);

    return 0;
}

void createEmptyStack(stack *s) {
    s->top = -1;
}

int isEmpty(stack *s) {
    return s->top == -1;
}

int isFull(stack *s) {
    return s->top == MAX - 1;
}

void push(stack *s, int value) {
    if (isFull(s)) {
        printf("A pilha está cheia, desempilhe um item antes de empilhar!\n");
        return;
    }
    s->top++;
    s->items[s->top] = value;
    printf("Valor %d empilhado.\n", value);
}

void pop(stack *s) {
    if (isEmpty(s)) {
        printf("A pilha está vazia, empilhe algo antes de desempilhar!\n");
        return;
    }
    printf("Valor desempilhado: %d\n", s->items[s->top]);
    s->top--;
}

void peek(stack *s) {
    if (isEmpty(s)) {
        printf("A pilha está vazia, empilhe algo primeiro.\n");
        return;
    }
    printf("Topo da pilha: %d\n", s->items[s->top]);
}

void showFullStack(stack *s) {
    if (isEmpty(s)) {
        printf("A pilha está vazia!\n");
        return;
    }
    printf("Conteúdo da pilha: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}
