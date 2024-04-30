#include <stdio.h>

int findMajority(int A[], int left, int right) {
    // base case: array only has 1 element:
    if (left == right) {
        return A[left];
    }

    // determine middle index
    int mid = (left + right) / 2;

    // recursively iterate over left and right subarray to find the majority element
    int leftMajority = findMajority(A, left, mid);
    int rightMajority = findMajority(A, mid + 1, right);

    // if left == right (same majority element for left and right subarray): return that
    if (leftMajority == rightMajority) {
        return leftMajority;
    }

    // if the left and right side do not have same majority element, iterate over current subarray
    // and count how often the majority elements of the right and left subarray occur
    int countLeft = 0;
    int countRight = 0;
    for (int i = left; i <= right; i++) {
        if (A[i] == leftMajority) {
            countLeft += 1;
        } else if (A[i] == rightMajority) {
            countRight += 1;
        }
    }

    // return the majority element that occurs more often in the entire subarray
    if (countLeft >= countRight) {
        return leftMajority;
    }
    return rightMajority;
}

// function to print an array
void printArray(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", A[i]);
    }
    printf("%d", A[n - 1]);
}

int main() {
    int A[] = {2, 2, 1, 2, 2, 1, 1, 1, 1};
    int n = sizeof(A)/sizeof(A[0]);

    int majorityElement = findMajority(A, 0, n - 1);

    printf("The majority element of the array A = [");
    printArray(A, n);
    printf("] is %d.", majorityElement);
    return 0;
}