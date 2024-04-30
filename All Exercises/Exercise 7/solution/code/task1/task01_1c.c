#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This solution uses pointers to pointers to allow multiple instances of
// stacks.

struct Node {
    int key;
    struct Node *next;
};

// Convention: new_stack points to NULL when the stack is empty.
struct Node** new() {
    struct Node **new_stack = malloc(sizeof(struct Node*));
    *new_stack = NULL;
    return new_stack;
}

bool is_empty(struct Node** S) {
    return (*S == NULL);
}

int pop(struct Node** S) {
    if (is_empty(S)) {
        return -1;
    }

    int top_value;
    top_value = (*S)->key;

    struct Node* temp = *S;
    *S = (*S)->next;
    free(temp);

    return top_value;
}

void push(struct Node** S, int x) {
    struct Node* new_node = malloc(sizeof(struct Node));

    new_node->key = x;
    new_node->next = *S;
    *S = new_node;
}

// Demo code starting here.
void print_stack_helper(struct Node *node) {
    if (node != NULL) {
        print_stack_helper(node->next);
        printf("%d ", node->key);
    }
}

void print_stack(struct Node **S, char *name) {
    if (is_empty(S) == 0) {
        printf("Stack %s is (from bottom to top): ", name);
        print_stack_helper(*S);
        printf("\n");
    }
    else {
        printf("The stack %s is empty.\n", name);
    }
}

int main() {
    struct Node **S1 = new();
    printf("The initial stack S1 is empty: %d\n", is_empty(S1));
    push(S1, 3);
    push(S1, 2);
    push(S1, 1);
    print_stack(S1, "S1");
    printf("Popped item: %d\n", pop(S1));
    print_stack(S1, "S1");
    push(S1, 4);
    print_stack(S1, "S1");
    printf("Popped item: %d\n", pop(S1));
    printf("Popped item: %d\n", pop(S1));
    printf("Popped item: %d\n", pop(S1));
    print_stack(S1, "S1");
    printf("Now I tried popping an empty stack: %d\n", pop(S1));

    struct Node **S2 = new();
    push(S2, 2);
    push(S2, 3);
    push(S2, 4);
    print_stack(S2, "S2");
    printf("Now I can pop an element from S2 and push that element in S1.\n");
    push(S1, pop(S2));
    print_stack(S2, "S2");
    print_stack(S1, "S1");
    return 0;
}