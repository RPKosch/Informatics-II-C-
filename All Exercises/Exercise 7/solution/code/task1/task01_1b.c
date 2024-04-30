#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int key;
    struct Node *next;
};

// S points to the head/top of the stack
struct Node *S;

// Convention: S is NULL when the stack is empty.
void new() {
    S = NULL;
}

bool is_empty() {
    return (S == NULL);
}

int pop() {
    if (is_empty() == 1) {
        return -1;
    }

    // We have two cases:
    // 1. S->next == NULL; the stack only contains one number. Replace S with
    //    NULL.
    // 2. S->next == NULL; the stack has at least two elements. Erase the head
    //    of the list and move the root to the next node.

    if (S->next == NULL) {
        int top_value = S->key;
        S = NULL;
        return top_value;
    }
    else {
        int top_value = S->key;
        struct Node *temp = S;
        S = S->next;
        free(temp);
        return top_value;
    }
}

// No need to return `bool` like in subtask a), because the push is always
// successful.
void push(int x) {
    // We have two cases here:
    // 1. The stack is empty (S == NULL). Create a new node for S.
    // 2. The stack is not empty. Add a new node to the head of the list and
    //    move the root to this new node.

    if (is_empty()) {
        S = malloc(sizeof(struct Node));
        S->key = x;
        S->next = NULL;
    }
    else {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->key = x;
        new_node->next = S;
        S = new_node;
    }
}

// Demo code starting here.
void print_stack_helper(struct Node *node) {
    if (node != NULL) {
        print_stack_helper(node->next);
        printf("%d ", node->key);
    }
}

void print_stack() {
    if (is_empty() == 0) {
        printf("Stack is (from bottom to top): ");
        print_stack_helper(S);
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