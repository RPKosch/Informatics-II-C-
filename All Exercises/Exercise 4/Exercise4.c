#include <stdio.h>
#include <math.h>

static void swapint(int list[], int first, int second){
    int tmp = list[first];
    list[first] = list[second];
    list[second] = tmp;
}


static void Merge(int array[], int l, int r, int m) {
    int Barray[20];
    for(int i = l; i <= m; i++) {
        Barray[i] = array[i];
    }
    for(int i = m+1; i <= r; i++) {
        Barray[r+m+1-i] = array[i];
    }
    int i = l;
    int j = r;

    for(int k = l; k <= r; k++) {
        if(Barray[i] < Barray[j]) {
            array[k] = Barray[i];
            i++;
        } else {
            array[k] = Barray[j];
            j--;
        }
    }

}

static void Mergesort(int array[], int l, int r) {
    if(l < r) {
        int m = (r+l)/2;
        Mergesort(array, l, m);
        Mergesort(array, m+1, r);
        Merge(array, l, r, m);
    }

}

//HeapSort

static void Heapify(int array[], int i, int length) {
    int m = i;
    int r = m*2 + 1;
    int l = m*2;
    if(l <= length && array[l]>array[m]){m = l;}
    if(r <= length && array[r]>array[m]){m = r;}
    if(i != m) {
        swapint(array, i, m);
        Heapify(array, m, length);
    }
}

static void BuildHeap(int array[], int length) {
    for(int x = length/2; x >= 0; x--) {
        Heapify(array, x, length);
    }
}

static void HeapSort(int array[], int length){
    int s = length;
    BuildHeap(array, length);
    for(int x = length; x >= 1; x--) {
        swapint(array, x, 0);
        s--;
        Heapify(array, 0, s);
    }
}



int main(){
    char string[] = "hallo";
    int l = sizeof(string)/sizeof(string[0]);
    printf_s("%d", l);
    printf("%d \n", l);

    int array[] = {2,4,5,7,1,2,3,6};
    int size = sizeof(array)/sizeof(array[0]);
    //Mergesort(array, 0, size-1);
    HeapSort(array, size-1);

    for(int x = 0; x < size; x++) {
        printf("%d ", array[x]);
    }

}