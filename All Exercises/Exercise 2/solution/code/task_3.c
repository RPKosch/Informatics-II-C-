#include <stdio.h>
#include <stdlib.h>

int moveCount = 0;

/**
 * Move disk n from src to dst via aux
*/
void hanoi(int n, char src, char aux, char dst) {
    if (n == 0) {
        return;
    }
    // move n-1 disks from source to auxiliary via destination
    hanoi(n - 1, src, dst, aux);
    
    // move the n-th disk from source to destination in 1 step
    printf("disk %d from %c to %c\n", n, src, dst);
    moveCount++;

    // move n-1 disks from auxiliary to destination via source
    hanoi(n - 1, aux, src, dst);
}

int main() {
    int n;

    printf("Enter the number of disks: ");
    scanf("%d", &n);

    printf("\nHanoi Tower Steps:\n");
    hanoi(n, 'A', 'B', 'C');

    printf("\nTotal number of moves: %d\n", moveCount);

    return 0;
}