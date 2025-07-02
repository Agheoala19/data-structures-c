// BST: WHAT IS IT?
// A BST (Binary Search Tree) is a binary tree where each node's left child has a smaller value, 
// and the right child has a larger value than the node itself.

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct BST BST;
typedef struct House House;

struct House {
	int id; // necessary for ordering the tree
	char* ownerName;
	int yearOfConstruction;
};

struct BST {
	House info;
	BST* leftChild;
	BST* rightChild;
};

House initHouse(int id, const char* ownerName, int yearOfConstruction) {
	House house;
	house.id = id;
	house.ownerName = (char*)malloc(sizeof(char) * (strlen(ownerName) + 1));
	strcpy(house.ownerName, ownerName);
	house.yearOfConstruction = yearOfConstruction;

	return house;
}

void printNode(House house) {
	printf("\nId: %d, owner name: %s, year of construction: %d", house.id, house.ownerName, house.yearOfConstruction);
}

void insertInBST(BST** root, House house) {
	if (*root == NULL) {
		BST* newNode = (BST*)malloc(sizeof(BST));
		newNode->info = house;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		*root = newNode;
	}
	else if (house.id < (*root)->info.id) {
		insertInBST(&((*root)->leftChild), house);
	}
	else {
		insertInBST(&((*root)->rightChild), house);
	}
}

void inOrder(BST* root) { // LrR - Left root Right = we cross the BST from left to root to right
	if (root != NULL) {
		inOrder(root->leftChild);
		printNode(root->info);
		inOrder(root->rightChild);
	}
}

void postOrder(BST* root) { // LRr - Left Right root = we cross the BST from left to right to root
	if (root != NULL) {
		postOrder(root->leftChild);
		postOrder(root->rightChild);
		printNode(root->info);
	}
}

void preOrder(BST* root) { // rLR - root Left Right = we cross the BST from root to left to right
	if (root != NULL) {
		printNode(root->info);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}

House returnByID(BST* root, int id) {
	if (root == NULL) {
		return initHouse(-1, "", 0); // if root is null or if the selected id doesn't exist in the tree
	}
	if (id == root->info.id) {
		return initHouse(root->info.id, root->info.ownerName, root->info.yearOfConstruction);
	}
	if (id < root->info.id) {
		return returnByID(root->leftChild, id);
	}
	if (id > root->info.id) {
		return returnByID(root->rightChild, id);
	}
}

void freeBST(BST** root) {
	if (*root != NULL) {
		freeBST(&(*root)->leftChild);
		freeBST(&(*root)->rightChild);
		free((*root)->info.ownerName);
		free(*root);
	}
}

int main() {
	BST* root = NULL;

	insertInBST(&root, initHouse(9, "John", 1976));
	insertInBST(&root, initHouse(17, "Mary", 2001));
	insertInBST(&root, initHouse(3, "Ann", 2022));
	insertInBST(&root, initHouse(12, "Bob", 1950));

	printf("\nCrossing BST in order:");
	inOrder(root); // the order of return based on id will be: 3 9 12 17
	printf("\n");

	printf("\nCrossing BST in post-order:");
	postOrder(root); // the order of return based on id will be: 3 12 17 9
	printf("\n");

	printf("\nCrossing BST in pre-order:");
	preOrder(root); // the order of return based on id will be: 9 3 17 12
	printf("\n");

	House house = returnByID(root, 12);
	printf("\nFunction returned house with id %d, owner name %s, year of construction %d.", house.id, house.ownerName, house.yearOfConstruction);
	// will return all information of the node with id 12

	freeBST(&root);

	return 0;
}
