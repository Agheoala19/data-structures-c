#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node Node;

struct Node {
  int info;
  Node* next;
};

void insertNodesInList(Node** head, int info) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->info = info;
  newNode->next = *head;
  *head = newNode;
}

void printNodesInfo(Node* head) {
    while(head != NULL){
      printf("\nInfo: %d", head->info);
      head = head->next;
    }
}

void freeNodesMemory(Node** head) {
  while ((*head) != NULL) {
		Node* copy = *head;
		*head = (*head)->next;
		free(copy);
	}
}

void main() {
  Node* head = NULL;
  for(int i = 0; i < 5; i++) {
    insertNodesInList(&head, i);
  }

  printNodesInfo(head);
  freeNodesMemory(&head);
}
