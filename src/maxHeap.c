#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct House House;
typedef struct MaxHeap MaxHeap;

struct House {
	int priority; //necessary for heapify
	char* ownerName;
	int yearOfConstruction;
};

struct MaxHeap {
	House* array;
	int length;
};

House initHouse(int priority, const char* ownerName, int yearOfConstruction) {
	House house;
	house.priority = priority;
	house.ownerName = (char*)malloc(sizeof(char) * (strlen(ownerName) + 1));
	strcpy(house.ownerName, ownerName);
	house.yearOfConstruction = yearOfConstruction;

	return house;
}

void printHouse(House house) {
	printf("\nPriority: %d, owner name: %s, year of construction: %d", house.priority, house.ownerName, house.yearOfConstruction);
}

void crossingMaxHeap(MaxHeap mh) {
	for (int i = 0; i < mh.length; i++) {
		printHouse(mh.array[i]);
	}
}

void heapify(MaxHeap mh, int index) {
	int parentIndex = index;
	int leftChildIndex = 2 * index + 1;
	int rightChildIndex = 2 * index + 2;

	if (leftChildIndex < mh.length && mh.array[parentIndex].priority < mh.array[leftChildIndex].priority) {
		parentIndex = leftChildIndex;
	}

	if (rightChildIndex < mh.length && mh.array[parentIndex].priority < mh.array[rightChildIndex].priority) {
		parentIndex = rightChildIndex;
	}

	if (parentIndex != index) { //verifying if the index of the parent was changed
		House temp = mh.array[index];
		mh.array[index] = mh.array[parentIndex];
		mh.array[parentIndex] = temp;

		if (parentIndex <= mh.length / 2 - 1) {
			heapify(mh, parentIndex); //recursion, if the current node still has children we start over on new index
		}
	}
}

House extractFromMaxHeap(MaxHeap* mh) { //extracts first node from the Max Heap
	House h = initHouse(mh->array[0].priority, mh->array[0].ownerName, mh->array[0].yearOfConstruction);
	House temp = mh->array[0];
	mh->array[0] = mh->array[mh->length - 1]; //replacing the first node with the last one
	mh->array[mh->length - 1] = temp;
	mh->length--; //deleting the last node which took the first node's informations
	heapify(*mh, 0); //reordering the MaxHeap

	return h;
}

int main() {

	//MaxHeap creation

	MaxHeap mh;
	mh.length = 4;
	mh.array = (House*)malloc(sizeof(House) * mh.length);

	mh.array[0] = initHouse(1, "John", 1976);
	mh.array[1] = initHouse(2, "Mary", 2001);
	mh.array[2] = initHouse(3, "Ann", 2022);
	mh.array[3] = initHouse(4, "Bob", 1950);

	printf("\nMaxHeap before filtering:");
	crossingMaxHeap(mh);
	printf("\n");

	//MaxHeap filtering

	for (int i = mh.length / 2 - 1; i >= 0; i--) {
		heapify(mh, i);
	}
	printf("\nMaxHeap after filtering:");
	crossingMaxHeap(mh);
	printf("\n");

	//MaxHeap extraction

	printf("\nExtracting the first node...");
	House h = extractFromMaxHeap(&mh);
	printf("\nExtracted first node:");
	printHouse(h);
	printf("\n");
	printf("\nMaxHeap after extraction:");
	crossingMaxHeap(mh);

	House* hArray = NULL;

	//Preventing memory leaks
	
	for (int i = 0; i < mh.length; i++) {
		free(mh.array[i].ownerName);
	}
	free(mh.array);

	return 0;
}
