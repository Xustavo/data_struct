/*
Atividade aula 3 - Pilhas
Escreva um programa, na linguagem de sua preferência, que execute a seguintes tarefas:
Escreva uma aplicação que leia 10 números
Se o número for par, empilhe numa pilha,
Se for ímpar, desempilhe um número da pilha, caso a pilha esteja vazia, esscreva na tela a mensagem: " Pilha vazia"
Se ao final do programa a pilha não estiver vazia, desempilhe todos os elementos, mostrando-os na tela.
Obs.: Crie as rotinas separadamente.
*/

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
void printRemainingItems(stack *s);

int main(){
    int a;  
    char buf[1024];  
    stack s; 
    createEmptyStack(&s);  

    for (int i = 0; i < MAX; i++) {
        do {
            printf("Digite um número: ");
            if (!fgets(buf, 1024, stdin)) {
                return 1; 
            }

            a = atoi(buf); 
        } while (a == 0); 

        if (a % 2 == 0) {
            push(&s, a);
        }
        else {
            pop(&s);
        }
    }

    printf("\nFinalizando programa...\n");
    printRemainingItems(&s);

    return 0;
}

void createEmptyStack(stack *s) {
    s->top = -1; 
}

int isEmpty(stack *s) {
    return s->top == -1;
}

void push(stack *s, int value) {
    s->top++;
    s->items[s->top] = value;
    printf("Valor %d empilhado.\n", value);
}

void pop(stack *s) {
    if (isEmpty(s)) {
        printf("Pilha Vazia!\n");
        return;
    }
    printf("Valor desempilhado: %d\n", s->items[s->top]); 
    s->top--; 
}

void printRemainingItems(stack *s){
    if (isEmpty(s)) {
        printf("A pilha está vazia.\n");
    } else {
        printf("Desempilhando itens restantes da pilha:\n");
        while (!isEmpty(s)) {
            pop(s);
        }
    }
}