#include <stdio.h>

// function to find the max sum of a subarray that crosses the middle part
int maxOverlap(int A[], int l, int m, int r){
    int lsum = 0;
    int rsum = 0;
    
    // initialize left and right sum to very small values
    int left = -9999;
    int right = -9999;

    // calculate the max sum of the left subarray
    for (int i = m; i>=l; i--){
        lsum += A[i];
        if (lsum > left){
            left = lsum;
        }
    }

    // calculate the max sum of the right subarray
    for (int i = m+1; i<=r; i++){
        rsum += A[i];
        if (rsum > right){
            right = rsum;
        }
    }

    // return the sum of the left and right subarrays
    return right + left;
}

// function to find the max subarray sum
int maxSubArray(int A[], int l, int r){

    // base case: array only has 1 element
    if (l == r){
        return A[l];
    }

    if (l < r){
        // determine middle index
        int m = (l+r)/2;

        // recursively find the max subarray sum in the left and right subarray
        int left = maxSubArray(A, l, m);
        int right = maxSubArray(A, m+1, r);

        // find the may subarray sum that crosses the middle index
        int overlap = maxOverlap(A, l, m, r);

        // compare the left, right, and overlap and return the max subarray sum
        if (right > left && right > overlap){
            return right;
        }
        else if (left > right && left > overlap){
            return left;
        }
        else {
            return overlap;
        }

    }
   
}

// function to print an array
void print_array(int A[], int n){
    for (int i = 0; i < n - 1; i++){
        printf("%d, ", A[i]);
    }
    printf("%d", A[n-1]);
}

int main(){
    int A[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = 8;

    int max_sum = maxSubArray(A, 0, n-1);
    
    printf("The sum of the maximum subarray in array A = [");
    print_array(A, n);
    printf("] is %d.", max_sum);
    return 0;

}