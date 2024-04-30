#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int key;
    struct Node *next;
};

struct Node *head, *tail;

// Convention: head = tail = NULL if the queue is empty
void new() {
    head = tail = NULL;
}

bool is_empty() {
    return (head == NULL && tail == NULL);
}

void enqueue(int x) {
    // We have two cases:
    // 1. The queue is empty: head == tail == NULL. We create a new node to
    //    which the head and tail get assigned.
    // 2. The queue is not empty. We create a new node and move the tail.

    if (is_empty()) {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->key = x;
        new_node->next = NULL;
        head = tail = new_node;
    }
    else {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->key = x;
        new_node->next = NULL;
        tail->next = new_node;
        tail = new_node;
    }
}

int dequeue() {
    if (is_empty()) {
        return -1;
    }

    // We have two cases:
    // 1. The queue only has one element: head == tail (notice that we don't
    //    have to check for head == NULL or tail == NULL, because that is taken
    //    care of by the `is_empty()` function in the `if` statement above).
    //    Delete the node and set head = tail = NULL.
    // 2. The queue has more than one element (head != tail): erase the node
    //    from the head and move the head pointer to the next node.

    if (head == tail) {
        int head_value = head->key;
        free(head);  // first free the memory, then assign NULL to head/tail
        head = tail = NULL;
        return head_value;
    }
    else {
        int head_value = head->key;
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return head_value;
    }
}

// Demo code starting here.
void print_queue() {
    if (is_empty()) {
        printf("The queue is empty.\n");
        return;
    }

    printf("The queue is (from head to tail): ");
    for (struct Node *node = head; node != NULL; node = node->next) {
        printf("%d ", node->key);
    }
    printf("\n");
}

int main() {
    new();
    printf("The initial queue is empty: %d\n", is_empty());
    printf("I now enqueue the values 3, 4 and 2\n");
    enqueue(3);
    enqueue(4);
    enqueue(2);
    print_queue();
    printf("I now dequeue (remove from the head)\n");
    printf("Dequeued value: %d\n", dequeue());
    print_queue();
    printf("Dequeued value: %d\n", dequeue());
    print_queue();
    printf("Enqueued value: 10\n");
    enqueue(10);
    print_queue();
    printf("Enqueued value: 20\n");
    enqueue(20);
    print_queue();
    printf("Dequeued value: %d\n", dequeue());
    print_queue();
    printf("Dequeued value: %d\n", dequeue());
    print_queue();
    printf("Dequeued value: %d\n", dequeue());
    print_queue();
    printf("Dequeued value: %d\n", dequeue());
    return 0;
}