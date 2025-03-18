#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* createNode(int data);
void insertAtFirst(Node** head, int val);
void insertAtEnd(Node** head, int val);
void insertAtPosition(Node** head, int position, int val);
void deleteAtFirst(Node** head);
void deleteAtEnd(Node** head);
void deleteAtPosition(Node** head, int position);
int evenNumbers(Node** head);
Node* evenNumbersList(Node** head);
float listAverage(Node** head);
void printList(Node** head);

int main() {
    Node* head = NULL;
    int choice, value, position;
    char input[100];

    do {
        printf("\nMenu:\n");
        printf("1. Insert a value at the end\n");
        printf("2. Insert a value at the beginning\n");
        printf("3. Insert a value at a specific position\n");
        printf("4. Delete the first value\n");
        printf("5. Delete the last value\n");
        printf("6. Delete a value at a specific position\n");
        printf("7. Count even numbers in the list\n");
        printf("8. Display the even numbers list\n");
        printf("9. Calculate the average of the list\n");
        printf("10. Display the list\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin); 
        choice = atoi(input);  
        
        switch (choice) {
            case 1:
                printf("Enter the value to insert at the end: ");
                fgets(input, sizeof(input), stdin); 
                value = atoi(input);  
                insertAtEnd(&head, value);
                break;
            case 2:
                printf("Enter the value to insert at the beginning: ");
                fgets(input, sizeof(input), stdin);  
                value = atoi(input);  
                insertAtFirst(&head, value);
                break;
            case 3:
                printf("Enter the position to insert the value: ");
                fgets(input, sizeof(input), stdin);  
                position = atoi(input);  
                printf("Enter the value to insert: ");
                fgets(input, sizeof(input), stdin);  
                value = atoi(input);  
                insertAtPosition(&head, position, value);
                break;
            case 4:
                deleteAtFirst(&head);
                break;
            case 5:
                deleteAtEnd(&head);
                break;
            case 6:
                printf("Enter the position to delete: ");
                fgets(input, sizeof(input), stdin);  
                position = atoi(input);  
                deleteAtPosition(&head, position);
                break;
            case 7:
                printf("Even numbers count: %d\n", evenNumbers(&head));
                break;
            case 8:
                {
                    Node* evenList = evenNumbersList(&head);
                    printf("Even numbers list: ");
                    printList(&evenList);
                }
                break;
            case 9:
                printf("Average of the list: %.2f\n", listAverage(&head));
                break;
            case 10:
                printf("Current list: ");
                printList(&head);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtFirst(Node** head, int val) {
    Node* newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(Node** head, int val) {
    Node* newNode = createNode(val);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtPosition(Node** head, int position, int val) {
    Node* newNode = createNode(val);
    if (position == 0) {
        insertAtFirst(head, val);
        return;
    }
    Node* temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtFirst(Node** head) {
    if (*head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    Node* temp = *head;
    *head = temp->next;
    free(temp);
}

void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    Node* temp = *head;
    if (temp->next == NULL) {
        free(temp);
        *head = NULL;
        return;
    }

    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void deleteAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("The list is empty!\n");
        return;
    }
    Node* temp = *head;
    if (position == 0) {
        deleteAtFirst(head);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range!\n");
        return;
    }
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

int evenNumbers(Node** head) {
    if (*head == NULL) {
        printf("The list is empty!\n");
        return 0;
    }
    int count = 0;
    Node* temp = *head;

    while (temp != NULL) {
        if (temp->val % 2 == 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

Node* evenNumbersList(Node** head) {
    if (*head == NULL) {
        printf("The list is empty!\n");
        return NULL;
    }
    Node* evenHead = NULL;  
    Node* temp = *head;

    while (temp != NULL) {
        if (temp->val % 2 == 0) {
            insertAtEnd(&evenHead, temp->val);
        }
        temp = temp->next;
    }
    return evenHead;
}

float listAverage(Node** head) {
    int sum = 0;
    int count = 0;
    Node* temp = *head;
    
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

void printList(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}
