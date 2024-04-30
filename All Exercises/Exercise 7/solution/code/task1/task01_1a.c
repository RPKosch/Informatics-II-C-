#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 1000

int S[MAX_STACK_SIZE];
int top;  // top = index showing the first empty cell in the array

void new() {
    top = 0;
}

bool is_empty() {
    return (top == 0);
}

int pop() {
    if (is_empty() == 1) {
        return -1;
    }
    top -= 1;
    return S[top];
}

// returns 1 if insertion is successful, 0 if it fails
bool push(int x) {
    if (top == MAX_STACK_SIZE) {
        return 0;
    }
    S[top] = x;
    top += 1;
    return 1;
}

// Demo code starting here.
void print_stack() {
    if (is_empty() == 0) {
        printf("Stack is (from bottom to top): ");
        for (int i = 0; i<top; i++) {
            printf("%d ", S[i]);
        }
        printf("\n");
    }
    else {
        printf("The stack is empty.\n");
    }
}

int main() {
    new();
    printf("The initial stack is empty: %d\n", is_empty());
    push(3);
    push(2);
    push(1);
    print_stack();
    printf("Popped item: %d\n", pop());
    print_stack();
    push(4);
    print_stack();
    printf("Popped item: %d\n", pop());
    printf("Popped item: %d\n", pop());
    printf("Popped item: %d\n", pop());
    print_stack();
    printf("Now I tried popping an empty stack: %d\n", pop());
    return 0;
}