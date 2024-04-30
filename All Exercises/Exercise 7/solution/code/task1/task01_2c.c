#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int key;
    struct Node *next;
};

// Create a struct which allows for returning a newly-created queue in the
// function new().
struct Queue {
    struct Node **head, **tail;
};

// We keep the convention from subtask b): head = tail = NULL if the queue is
// empty.
struct Queue new() {
    struct Queue new_queue;
    new_queue.head = malloc(sizeof(struct Node*));
    new_queue.tail = malloc(sizeof(struct Node*));

    // Parenthesis around `new_queue.head` and similar are added for clarity.
    *(new_queue.head) = *(new_queue.tail) = NULL;
    return new_queue; 
}

bool is_empty(struct Queue q) {
    return (*(q.head) == NULL && *(q.tail) == NULL);
}

void enqueue(struct Queue q, int x) {
    // We have two cases:
    // 1. The queue is empty: *(q.head) == *(q.tail) == NULL. We create a new
    //    node to which the head and tail get assigned.
    // 2. The queue is not empty. We create a new node and move the tail.

    if (is_empty(q)) {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->key = x;
        new_node->next = NULL;
        *(q.head) = *(q.tail) = new_node;
    }
    else {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->key = x;
        new_node->next = NULL;
        (*(q.tail))->next = new_node;
        *(q.tail) = new_node;
    }
}

int dequeue(struct Queue q) {
    if (is_empty(q)) {
        return -1;
    }

    // We have two cases:
    // 1. The queue only has one element: head node == tail node (notice that we
    //    don't have to check for head == NULL or tail == NULL, because that is
    //    taken care of by the `is_empty()` function in the `if` statement
    //    above). Delete the node and set head = tail = NULL.
    // 2. The queue has more than one element (head node != tail node): erase
    //    the node from the head and move the head pointer to the next node.

    if (*(q.head) == *(q.tail)) {
        int head_value = (*(q.head))->key;
        free(*(q.head));  // first free the memory, then assign NULL to head/tail
        *(q.head) = *(q.tail) = NULL;
        return head_value;
    }
    else {
        int head_value = (*(q.head))->key;
        struct Node *temp = *(q.head);
        *(q.head) = (*(q.head))->next;
        free(temp);
        return head_value;
    }
}

// Demo code starting here.
void print_queue(struct Queue q, char *name) {
    if (is_empty(q)) {
        printf("The queue %s is empty.\n", name);
        return;
    }

    printf("The queue %s is (from head to tail): ", name);
    for (struct Node *node = *(q.head); node != NULL; node = node->next) {
        printf("%d ", node->key);
    }
    printf("\n");
}

int main() {
    struct Queue q1 = new();
    printf("The queue q1 is empty: %d\n", is_empty(q1));
    printf("I now enqueue the values 3, 4 and 2\n");
    enqueue(q1, 3);
    enqueue(q1, 4);
    enqueue(q1, 2);
    print_queue(q1, "q1");
    printf("I now dequeue (remove from the head)\n");
    printf("Dequeued value: %d\n", dequeue(q1));
    print_queue(q1, "q1");
    printf("Dequeued value: %d\n", dequeue(q1));
    print_queue(q1, "q1");
    printf("Enqueued value: 10\n");
    enqueue(q1, 10);
    print_queue(q1, "q1");
    printf("Enqueued value: 20\n");
    enqueue(q1, 20);
    print_queue(q1, "q1");
    printf("Dequeued value: %d\n", dequeue(q1));
    print_queue(q1, "q1");
    printf("Dequeued value: %d\n", dequeue(q1));
    print_queue(q1, "q1");
    printf("Dequeued value: %d\n", dequeue(q1));
    print_queue(q1, "q1");
    printf("Dequeued value: %d\n", dequeue(q1));

    printf("\nNow I create another queue\n");
    struct Queue q2 = new();
    enqueue(q2, 12);
    enqueue(q2, 7);
    enqueue(q2, 9);
    print_queue(q2, "q2");

    printf("\nNow I transfer one element from q2 to q1:\n");
    enqueue(q1, dequeue(q2));
    print_queue(q1, "q1");
    print_queue(q2, "q2");
    return 0;
}