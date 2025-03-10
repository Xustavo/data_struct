#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct queue {
    int arr[MAX];
    int back;
    int front;
} queue;

void createEmptyQueue(queue *q);
int isEmpty(queue *q);
int isFull(queue *q);
void enqueue(queue *q, int value);
void dequeue(queue *q);
void peek(queue *q);
void showFullQueue(queue *q);

int main(){

    queue q;
    createEmptyQueue(&q);
    int choice, value;

    while (1) {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Show Queue\n");
        printf("5. Exit\n");

        printf("Enter your choice (1-5): ");
        char choiceStr[10];
        fgets(choiceStr, sizeof(choiceStr), stdin);
        choice = atoi(choiceStr);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                fgets(choiceStr, sizeof(choiceStr), stdin);
                value = atoi(choiceStr);
                enqueue(&q, value);
                break;

            case 2: 
                dequeue(&q);
                break;

            case 3: 
                peek(&q);
                break;

            case 4: 
                showQueue(&q);
                break;

            case 5:
                printf("Exiting...\n");
                return 0; 

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

void createEmptyQueue(queue *q){
    q->front = 0;
    q->back = -1;
}

int isEmpty(queue *q){
    return q->back < q->front;
}

int isFull(queue *q){
    return q->front == MAX - 1;
}

void enqueue(queue *q, int value){
    if(isFull(q)){
        printf("Queue is full, dequeue some value to input another\n");
        return;
    }
    q->back++;
    q->arr[q->back] = value;
    printf("%d added to queue\n", value);
}

void dequeue(queue *q){
    if(isEmpty(q)){
        printf("Nothing in queue, enqueue smth so u can dequeue smth\n");
        return;
    }
    printf("%d dequeued from queue\n", q->arr[q->front]);
    q->front++;
}

void peek(queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
    } else {
        printf("Front of the queue: %d\n", q->arr[q->front]);
    }
}

void showQueue(queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents: ");
    for (int i = q->front; i <= q->back; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}