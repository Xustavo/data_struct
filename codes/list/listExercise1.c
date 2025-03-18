/*
Considere uma lista contendo números inteiros positivos. Faça uma função que:
Retorne quantos números pares existem na lista.  
Retorne uma nova lista contendo apenas os números pares da lista.  
Retorne a média da lista.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    Node* next;
} node;

struct *Node createNode(int data);
void insertAtFirst(struct Node** head, int val);
void insertAtEnd(struct Node** head, int val);
void insertAtPosition(struct Node** head, int position, int val);
void deleteAtFirst(struct Node** head);
void deletAtEnd(struct Node** head);
void deleteAtPosition(struct Node** head, int position);
int evenNumbers(struct Node** head);
struct *Node evenNumbersList(struct Node** head);
float listAverage(struct Node** head);
void printList(struct Node** head);

int main(){

    return 0;
}

struct *Node createNode(int data){
    struct *Node newNode = (struct *Node)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = null;

    return newNode;
}

void insertAtFirst(struct Node** head, int val){
    struct *Node newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct Node** head, int val){
    struct *Node newNode = createNode(val);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    struct *Node temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtPosition(struct Node** head, int position, int val){
    struct *Node newNode = createNode(val);
    if(position == 0){
        insertAtFirst(head, val);
    }
    struct *Node temp = *head;
    for(int i = 0; temp != NULL && i < position -1; i++){
        temp = temp->next;
    }

    if(temp == NULL){
        printf("Posição fora de alcance\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtFirst(struct Node** head){
    if(*head == NULL){
        printf("A lista está vazia!\n");
        return;
    }

    struct *Node temp = *head;
    *head = temp->next;
    free(temp);
}

void deletAtEnd(struct Node** head){
    if(*head == null){
        printf("A lista está vazia!\n");
        return;
    }

    struct *Node temp = *head;
    if(temp->next == NULL){
        free(temp);
        *head = NULL;
        return;
    }

    while(temp->next->next != NULL){
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void deleteAtPosition(struct Node** head, int position){
    if (*head == NULL) {
        printf("A lista está vazia!\n");
        return;
    }
    struct Node* temp = *head;
    if (position == 0) {
        deleteFromFirst(head);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Posição fora de alcance!\n");
        return;
    }
    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

int evenNumbers(struct Node** head){
    if(*head == NULL){
        printf("A lista está vazia!\n");
        return;
    }
    int count = 0;
    struct *Node temp = *head;

    while(temp != NULL){
        if(temp->next %2 == 0){
            count++;
        }
        temp = temp->next;
    }
    return count;
}

struct *Node evenNumbersList(struct Node** head){
    if(head == NULL){
        printf("A lista está vazia!\n");
        return;
    }
    struct Node* evenHead = NULL;  
    struct Node* temp = head;

    while(temp != NULL){
        if(temp->next % 2 == 0){
            insertAtEnd(&evenHead, temp->val);
        }
        temp = temp->next;
    }
    return evenHead;
}

float listAverage(struct Node** head){
    int sum = 0;
    int count = 0;
    struct Node* temp = head;
    
    while (temp != NULL) {
        sum += temp->val;
        count++;
        temp = temp->next;
    }
    
    if (count == 0) {
        return 0; 
    }
    
    return (float)sum / count;
}

void printList(struct Node** head){
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}