#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
	int info;
	Node* next;
};

void put(Node** queue, int info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = info;
	newNode->next = NULL;

	if (*queue == NULL) {
		*queue = newNode;
	}
	else {
		Node* temp = *queue;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
} //put function inserts nodes at the tail of the queue (LIFO - Last In First Out)

int get(Node** queue) {
	if (*queue == NULL) {
		return 0;
	}

	int info = (*queue)->info;
	Node* temp = *queue;
	*queue = (*queue)->next;
	free(temp);

	return info;
} 

void printQueue(Node* queue) {
	if (queue == NULL) {
		printf("\nQueue is empty!");
		return;
	}

	printf("\nQueue contents: ");
	while (queue != NULL) {
		printf("%d ", queue->info);
		queue = queue->next;
	}
	printf("\n");
}

void main() {
	Node* queue = NULL;

	put(&queue, 10);
	put(&queue, 20);
	put(&queue, 30);

	printQueue(queue); // 10 20 30

	printf("Get node: %d\n", get(&queue)); //will return  10
	printf("Get node: %d\n", get(&queue)); //will return  20
	printf("Get node: %d\n", get(&queue)); //will return  30
	printf("Get node: %d\n", get(&queue)); //will return  0
}
