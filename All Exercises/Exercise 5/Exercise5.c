#include <stdio.h>
#include <math.h>$

static void swapints(int array[], int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


int main(){
    printf("Checking\n");
    int array[2] = {1, 2};
    swapints(array, 0, 1);
    printf("%d, %d", array[0], array[1]);
}