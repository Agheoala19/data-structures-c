#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node Node;

struct Node {
  int info;
  Node* prev;
  Node* next;
};

void insertNodesInList(Node** head, Node** tail, int info) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->info = info;
  newNode->next = *head;
  newNode->prev = NULL;

  if ((*head) == NULL) {
		*head = *tail =  newNode;
	}
	else {
		(*head)->prev = newNode;
		*head = newNode;
	}
}

void printNodesInfo(Node* head) {
	while (head != NULL) {
		printf("Info: %d\n", head->info);
    head = head->next;
	}
}

void freeNodesMemory(Node** head, Node** tail) {
    while (*head != NULL) {
        Node* copy = *head;
        *head = (*head)->next;
        free(copy);
    }
    *tail = NULL;
}

void main(){
  Node* head = NULL;
  Node* tail = NULL;

  for (int i = 0; i < 5; i++) {
        insertNodesInList(&head, &tail, i);
  }

  printNodesInfo(head);

  freeNodesMemory(*head, *tail);
}
