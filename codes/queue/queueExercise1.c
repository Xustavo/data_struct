/*
Considere uma lista contendo números inteiros positivos. Faça uma função que:
Retorne quantos números pares existem na lista.  
Retorne uma nova lista contendo apenas os números pares da lista.  
Retorne a média da lista.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct queue {
    int arr[MAX];
    int front;
    int back;
} queue;

void createEmptyQueue(queue *q);
bool isEmpty(queue *q);
bool isFull(queue *q);
void enqueue(queue *q, int value);
void dequeue(queue *q);
void showEvenQuantityInQueue(queue *q);
void showQueueAverage(queue *q);
void filterEvenQueue(queue *q);
void showFullQueue(queue *q);

int main() {
    queue q;
    createEmptyQueue(&q);

    char input[10];
    int option;

    while (true) {
        printf("\n--- Menu ---\n");
        printf("1. Inserir na fila (enqueue)\n");
        printf("2. Remover da fila (dequeue)\n");
        printf("3. Mostrar quantidade de números pares na fila\n");
        printf("4. Mostrar média dos elementos da fila\n");
        printf("5. Mostrar todos os elementos da fila\n");
        printf("6. Filtrar os elementos pares da fila e retorná-los\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        fgets(input, sizeof(input), stdin);
        option = atoi(input);

        switch (option) {
            case 1:
                printf("Digite um valor para inserir na fila: ");
                fgets(input, sizeof(input), stdin);
                int value = atoi(input);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                showEvenQuantityInQueue(&q);
                break;
            case 4:
                showQueueAverage(&q);
                break;
            case 5:
                showFullQueue(&q);
                break;
            case 6:
                filterEvenQueue(&q);
                break;
            case 7:
                printf("Encerrando o programa.\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}

void createEmptyQueue(queue *q) {
    q->front = 0;
    q->back = -1;
}

bool isEmpty(queue *q) {
    return q->front > q->back;
}

bool isFull(queue *q) {
    return q->back == MAX - 1;
}

void enqueue(queue *q, int value) {
    if (isFull(q)) {
        printf("A fila está cheia!\n");
        return;
    }

    q->back++;
    q->arr[q->back] = value;
    printf("Valor inserido: %d\n", value);
}

void dequeue(queue *q) {
    if (isEmpty(q)) {
        printf("A fila está vazia!\n");
        return;
    }
    printf("Valor retirado da fila: %d\n", q->arr[q->front]);
    q->front++;
}

void showEvenQuantityInQueue(queue *q) {
    if (isEmpty(q)) {
        printf("A fila está vazia!\n");
        return;
    }

    int count = 0;

    for (int i = q->front; i <= q->back; i++) {
        if (q->arr[i] % 2 == 0) {
            count++;
        }
    }

    printf("Existem %d números pares na fila\n", count);
}

void showQueueAverage(queue *q) {
    if (isEmpty(q)) {
        printf("A fila está vazia!\n");
        return;
    }

    int sum = 0, count = 0;

    for (int i = q->front; i <= q->back; i++) {
        sum += q->arr[i];
        count++;
    }

    double result = (double)sum / count;

    printf("A média da fila é: %.2f\n", result);
}

void filterEvenQueue(queue *q){

    queue evenQueue;
    createEmptyQueue(&evenQueue);

    for(int i = q->front; i<=q->back; i++){
        if(q->arr[i] %2 == 0){
            enqueue(&evenQueue, q->arr[i]);
        }
    }

    showFullQueue(&evenQueue);
}

void showFullQueue(queue *q) {
    if (isEmpty(q)) {
        printf("A fila está vazia!\n");
        return;
    }

    printf("Elementos na fila: ");
    for (int i = q->front; i <= q->back; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}
