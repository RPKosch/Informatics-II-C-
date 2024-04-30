#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This code for queues is copied from task 1.2.
// -----------------------
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
// -------------------

// Solution from here.
void generate(int n) {
    int printed = 0, current_value;
    new();
    enqueue(1);
    for (printed = 0; printed < n; printed++) {
        current_value = dequeue();
        printf("%d ", current_value);
        enqueue(3*current_value + 1);
        enqueue(3*current_value + 2);
    }
}

int main() {
    generate(10);
    return 0;
}