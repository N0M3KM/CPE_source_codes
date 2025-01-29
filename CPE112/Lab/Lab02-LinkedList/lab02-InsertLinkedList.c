// 67070501016 Drarun Yookphan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{ 
    int data;
    struct Node *next;
}Node;

void printNodes(Node *head){
    Node *ptr = head;
    int count = 0;
    while(ptr!=NULL){
        count++;
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }

    if (count==0){
        printf("none");
    }
}

void insertHead(Node **head, int value) {
    Node *newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(Node **head, int value) {
    Node *newNode, *ptr;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(*head==NULL){
        *head = newNode;
    }else{
        ptr = *head;
        while (ptr->next != NULL) { 
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

void insertLeft(Node **head, int num, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        free(newNode);
        return;
    }
    Node *ptr = *head;
    Node *prePtr = NULL;
    while (ptr != NULL && ptr->data != num) {
        prePtr = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL) {
        free(newNode);
        return;
    }

    if (prePtr == NULL) {
        newNode->next = *head;
        *head = newNode;
    } else {
        prePtr->next = newNode;
        newNode->next = ptr;
    }
}

int main() {
    int num, value;
    Node *head = NULL;

    while (1) {
        char choice[10]; 
        scanf("%s", choice);

        if (strcmp(choice, "END") == 0) {
            break;
        } else if (strcmp(choice, "INSH") == 0) {
            scanf("%d", &value);
            insertHead(&head, value);
        } else if (strcmp(choice, "INSE") == 0) {
            scanf("%d", &value);
            insertEnd(&head, value);
        } else if (strcmp(choice, "INSL") == 0) {
            scanf("%d %d", &num, &value);
            insertLeft(&head, num, value);
        }
    }

    printNodes(head);

    return 0;
}