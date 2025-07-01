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

void push(Node** top, int info) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->info = info;
  newNode->next = *top;
  *top = newNode;
} // push function inserts nodes at the head of the stack (FIFO - First In First Out)

int pop(Node** top) {
  if(*top == NULL)
    return 0;

  int val = (*top)->info;
  Node* temp = *top;
  *top = (*top)->next;
  free(temp);

  return val;
}

void printStack(Node* top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents:\n");
    while (top != NULL) {
        printf("%d\n", top->info);
        top = top->next;
    }
}

void main() {
  Node* stack = NULL;

  push(&stack, 10);
  push(&stack, 20);
  push(&stack, 30);

  printStack(stack); // 30 20 10

  printf("Pop node: %d\n", pop(&stack)); //will return  30
  printf("Pop node: %d\n", pop(&stack)); //will return  20
  printf("Pop node: %d\n", pop(&stack)); //will return  10
  printf("Pop node: %d\n", pop(&stack)); //will return  0
}
