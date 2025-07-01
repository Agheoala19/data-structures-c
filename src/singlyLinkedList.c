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

//function to convert a list to an array; it works with Stack, Queue and Double List as well
//what we do: 1. we count how many nodes the list has; 2. memory to our array based on the count we got; 
//3. we navigate, with a for loop, the array giving it's current element the value of the current node's info; 4. we return the count after finishing
int listToArray(Node* head, int** array) {
	int count = 0;
	Node* temp = head;
	while(temp != NULL) {
		count++;
		temp = temp->next;
	}

	*array = (int*)malloc(count * sizeof(int));

	temp = head;
	for (int i = 0; i < count; i++) {
        	(*array)[i] = temp->info;
        	temp = temp->next;
    	}

	return count;
}

void main() {
  Node* head = NULL;
  for(int i = 0; i < 5; i++) {
    insertNodesInList(&head, i);
  }

  int* v = NULL;
  int n = listToArray(head, &v);
	
  printNodesInfo(head);
  printf("\nArray: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
  free(v);
  freeNodesMemory(&head);
}
