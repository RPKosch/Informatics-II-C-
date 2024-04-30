#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Check the symbols in index i and index j
*/
int isPalindrome(char X[], int i, int j) {
    if(j<=i) {
        return 1;
    }
    if(X[i] != X[j]) {
        return 0;
    }
    return isPalindrome(X, i+1, j-1);
}

int main() {
    char X[] = "1a_b3cD45t54Dc3b_a1";

    if (isPalindrome(X, 0, sizeof(X)-2) == 1) {
        printf("This is a Palindrome.");
    }
    else {
        printf("This is not a Palindrome.");
    }

    return 0;
}