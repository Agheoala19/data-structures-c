//WHAT'S AN HASH TABLE? WHY IS IT HELPFUL?
//An Hash Table it's a type of data structure that allows saving values based on a specific key (key-value pairings), this is helpful for fast find, insert and delete
//The index of each value it's determined by an hash function that converts the key(for example an ID) into an index, ex: hash(key) = key % length, where length is
//the length of the Hash Table

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node Node;
typedef struct HashTable HashTable;

struct Node {
	int info;
	Node* next;
};

struct HashTable {
	int length;
	Node** array;
};

void insertList(Node** head, int info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = *head;
	newNode->info = info;
	*head = newNode;
}

void printList(Node* head) {
	while (head != NULL) {
		printf("\nNode: %d", head->info);
		head = head->next;
	}
}

void freeList(Node** head) {
	while ((*head) != NULL) {
		Node* temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

HashTable initTable(int length) {
	HashTable table;
	table.length = length;
	table.array = (Node**)malloc(length * sizeof(Node*));
	for (int i = 0; i < length; i++) {
		table.array[i] = NULL;
	}
	return table;
}

int hash(int length, int info) {
	return info % length;
}

void insertInHashTable(HashTable* table, int info) {
	if (table->length > 0) {
		int index = hash(table->length, info);
		if (index >= 0 && index < table->length) {
			insertList(&(table->array[index]), info);
		}
	}
} //we create our index by using the hash function then we insert a list to the specific index to prevent collision
//by inserting a list in a specific element of an array (determined by the index of our value) we apply the chaining method for preventing collision

void printHashTable(HashTable* table) {
	for (int i = 0; i < table->length; i++) {
		printf("\nIndex: %d", i);
		printList(table->array[i]);
	}
}

void freeHashTable(HashTable* table) {
	for (int i = 0; i < table->length; i++) {
		freeList(&(table->array[i]));
	}
	free(table->array);
}

void main() {
	Node* head = NULL;

	int v[] = { 121, 67, 20, 5 }; 
	HashTable table = initTable(4);

	for (int i = 0; i < 4; i++) {
		insertInHashTable(&table, v[i]);
	}

	printHashTable(&table);
	freeHashTable(&table);
}
