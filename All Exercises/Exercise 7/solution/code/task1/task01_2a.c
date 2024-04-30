#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 1000

int Q[MAX_QUEUE_SIZE];
int head, tail;

void new() {
    head = tail = 0;
}

bool is_empty() {
    return (head == tail);
}

// Returns 1 if the operation was successful, 0 - otherwise.
bool enqueue(int x) {
    // Checking for a full queue: if tail + 1 == head (in terms of modulo), then
    // the tail will point to the same array cell as the head. But the tail
    // should always refer to an empty cell! Also, if we allow doing enqueues
    // which result in tail == head, then we would have no way of actually
    // knowing whether the queue is empty of full (because we check for head ==
    // tail in emptiness). The solution is to reject enqueues which lead to tail
    // == head.

    int next_index = (tail + 1) % MAX_QUEUE_SIZE;
    if (next_index == head) {
        return 0;
    }

    Q[tail] = x;
    tail = (tail + 1) % MAX_QUEUE_SIZE;
    return 1;
}

int dequeue() {
    if (is_empty()) {
        return -1;
    }

    int head_value = Q[head];
    head = (head + 1) % MAX_QUEUE_SIZE;
    return head_value;
}

// Demo code starting here.
void print_queue() {
    if (is_empty()) {
        printf("The queue is empty.\n");
        return;
    }

    printf("The queue is (from head to tail): ");
    int i;
    for (i = head; i != tail; i = (i + 1) % MAX_QUEUE_SIZE) {
        printf("%d ", Q[i]);
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