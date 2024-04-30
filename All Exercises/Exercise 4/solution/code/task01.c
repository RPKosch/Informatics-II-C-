#include <stdio.h>
#include <stdlib.h>

int find_closest_modified_binary_search(int A[], int low, int high, int t){
    // initialize the closest element to the first element
    int closest = A[low];

    while (low <= high){
        // determine middle index
        int mid = (low + high) / 2;

        // if middle element is closer to target, update closest 
        if (abs(A[mid] -t) < abs(closest -t)){ 
            closest = A[mid];
        }

        // middle element is the target, return
        if (A[mid] == t){
            return A[mid];
        }
        else if (A[mid] < t){ // if t is larger than middle element, continue search in right subarray
            low = mid + 1;
        }
        else { // if t is smaller than middle element, continue search in left subarray
            high = mid - 1;
        }
    }
    return closest;

} 


int find_closest_divide_conquer(int A[], int low, int high, int t){
    // base case
    if (low == high){
        return A[low];
    }
    if (t <= A[low])
        return A[low];
    if (t >= A[high])
        return A[high];

    // Find middle index
    int mid = (low + high) / 2;

    // find closest in left and right subarray
    int left_closest = find_closest_divide_conquer(A, low, mid, t);
    int right_closest = find_closest_divide_conquer(A, mid + 1, high, t);

    // Compare which one is closer
    if (abs(A[mid] - t) < abs(left_closest - t) && abs(A[mid] - t) < abs(right_closest - t))
        return A[mid];
    else if (abs(left_closest - t) < abs(right_closest - t))
        return left_closest;
    else
        return right_closest;

}

// function to print an array
void print_array(int A[], int n){
    for (int i = 0; i < n - 1; i++){
        printf("%d, ", A[i]);
    }
    printf("%d", A[n-1]);
}


int main(){
    int A[] = {2, 5, 10, 12, 15, 24, 32};
    int n = sizeof(A) / sizeof(A[0]); // length of the array A
    int t = 11;

    int closest_number = find_closest_divide_conquer(A, 0, n-1, t);
    
    printf("The closest number to %d in array A = [", t);
    print_array(A, n);
    printf("] is %d.\n", closest_number);
    return 0;
}