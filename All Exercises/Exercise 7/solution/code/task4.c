#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Code copied from task 1.1
// -------------------
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
// -----------------

// Solution starts here.
struct Node **sort_stack(struct Node **S) {
    struct Node **all_elements = new(), **temp_stack = new();
    int x, y;

    // We have to return the same stack S at the end, so push all the numbers
    // from S onto a separate stack and construct the prefix directly in S. 
    while (is_empty(S) == 0)
        push(all_elements, pop(S));

    // The first element already forms a sorted prefix.
    push(S, pop(all_elements));

    while (is_empty(all_elements) == 0) {
        x = pop(all_elements);  // we try to insert `x` into the prefix
        while (is_empty(S) == 0) {
            y = pop(S);
            if (y < x) {
                push(temp_stack, y);
            }
            else {
                // popped a number smaller than `x`, this means that we put in
                // all of the larger numbers in `temp_stack`.
                push(S, y);
                break;
            }
        }
        push(S, x);
        // Put back the larger numbers:
        while (is_empty(temp_stack) == 0)
            push(S, pop(temp_stack));
    }
    return S;
}

// Demo code starts here.
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
    struct Node **S = new();
    push(S, 1);
    push(S, 3);
    push(S, 2);
    push(S, 4);
    print_stack(S, "S");
    S = sort_stack(S);
    print_stack(S, "S");
    return 0;
}