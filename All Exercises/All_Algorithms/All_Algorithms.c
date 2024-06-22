#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define queuesize 5

int tstack = 0;
int S[100];

int bqueue = 0;
int tailqueue = 0;
int Q[queuesize];

static void push(int x){
    S[tstack] = x;
    tstack++;
    printf("%d", tstack);
}

static int pop(){
    tstack--;
    return S[tstack];
}

static void enqueue(int x){
    Q[bqueue] = x;
    bqueue+1 % queuesize;
}

static int dequeue(){
    int tmp = Q[tailqueue];
    tailqueue+1% queuesize;
    return tmp;
}

static void swapint(int array[], int x, int y){
    int tmp = array[x];
    array[x] = array[y];
    array[y] = tmp;
}

static void printall(int array[], int length) {
    printf("\n[");
    for (int x = 0; x < length-1; x++) {
        printf("%d, ", array[x]);
    }
    printf("%d]", array[length-1]);
}

static void bubblesort(int array[], int length){
    for(int x = length; x > 0; x--){
        for(int y = 1; y < x; y++ ){
            if(array[y] < array[y-1]){
                swapint(array, y, y-1);
            }
        }
    }
}

static void selectionsort(int array[], int length){
    for(int x = 0; x < length; x++){
        int c = x;
        for(int y = x; y < length; y++ ){
            if(array[y] < array[c]){
                c = y;
            }
        }
        swapint(array, c, x);
    }
}

static void insertionsort(int array[], int length){
    for(int x = 1; x < length; x++){
        int c = array[x];
        int j = x-1;
        while(j >= 0 && array[j] > c){
            array[j+1] = array[j];
            j--;
            }
        array[j+1] = c;
    }
}

static void Merge(int array[], int l, int r, int m){
    int B[r+1];
    for(int x = 0; x <= m; x++){
        B[x] = array[x];
    }
    for(int x = m+1; x <= r; x++){
        B[x] = array[m+1+r-x];
    }
    int i = l;
    int j = r;
    for(int k = l; k <= r; k++){
        if(B[i] < B[j]){
            array[k] = B[i];
            i++;
        } else {
            array[k] = B[j];
            j--;
        }
    }
}

static void Mergesort(int array[], int l, int r){
    if(l<r){
        int m = (r + l) / 2;
        Mergesort(array, l, m);
        Mergesort(array, m+1, r);
        Merge(array, l, r, m);
    }
}

static void Heapify(int array[], int i, int length){
    int m = i;
    int l = m*2 + 1;
    int r = m*2 + 2;

    if(l <= length && array[l] > array[m]){
        m = l;
    }
    if(r <= length && array[r] > array[m]){
        m = r;
    }
    if(m != i){
        swapint(array, m, i);
        Heapify(array, m, length);
    }
}

static void buildHeap(int array[], int length){
    for(int x = (length)/2; x >= 0; x--){
        Heapify(array, x, length);
    }
}

static void Heapsort(int array[], int r){
    int len = r;
    buildHeap(array, r);
    for(int x = r; x > 0; x--){
        swapint(array, x, 0);
        len--;
        Heapify(array, 0, len);
    }
}

static int HoarePartitioning(int array[], int l, int r){
    int x = array[r];
    int i = l-1;
    int j = r+1;
    while(1) {
        do {
        j--;
        } while (array[j] > x);
        do{
            i++;
        }while(array[i] < x);

        if(i < j){
            swapint(array, i, j);
        } else {
            return i;
        }
    }

}

// With j -> l to m and m+1 to r -
// With i -> l to m-1 and m to r

static void Quicksort(int array[], int l, int r){
    if(l < r){
        int m = HoarePartitioning(array, l, r);
        Quicksort(array, l, m-1);
        Quicksort(array, m, r);
    }
}

int M[30][30];
int d[] = {3, 2, 4, 5, 1};
int HAN[30];
int c[30][30];
char str1[] = "GGTTCATATHEYHOOOLO", str2[] = "GTATCTATHEHO";

void updatematrix() {
    for (int x = 0; x < 30; x++) {
        for (int y = 0; y < 30; y++) {
            M[x][y] = -1;
            HAN[y] = -1;
            c[x][y] = -1;
        }
    }
}

int matrixmemo(int i, int j) {
    if (i == j) {
        return 0;
    }
    if (M[i][j] > -1) {
        return M[i][j];
    }
    for (int k = i; k < j; k++) {
        int q = matrixmemo(i, k) + matrixmemo(k + 1, j) + d[i - 1] * d[k] * d[j];
        if (M[i][j] == -1 || q < M[i][j]) {
            M[i][j] = q;
        }
    }
    return M[i][j];
}

int HanoiMemo(int n, int A, int B, int C){
    if(n==1){return 1;}
    if(HAN[n] != -1){ return HAN[n];}
    HAN[n] = HanoiMemo(n-1, A, C, B) + 1 + HanoiMemo(n-1, C, B, A);
    return HAN[n];
}

// Function to return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// LCS memoization function
int LCSmemo(int i, int j) {
    if (i == -1 || j == -1) {
        return 0;
    }
    if (c[i][j] != -1) {
        return c[i][j];
    }
    if (str1[i] == str2[j]) { // Use x[i-1] and y[j-1] to correctly index 0-based strings
        c[i][j] = 1 + LCSmemo(i-1, j-1);
    } else {
        c[i][j] = max(LCSmemo(i, j-1), LCSmemo(i-1, j));
    }
    return c[i][j];
}

void printLCS(int i, int j){
    if(i == -1 || j == -1){return; }
    if(c[i][j] == c[i-1][j]){ printLCS(i-1, j); }
    else if(c[i][j] == c[i][j-1]){ printLCS(i, j-1); }
    else {
        printLCS(i-1, j-1);
        printf("%c", str1[i]);
    }
}

int main() {
    char string[] = "hallllloo";
    int size = strlen(string);

    int array1[] = {5, 4, 3, 2, 1, 0};
    int array2[] = {5, 4, 3, 2, 1, 0};
    int array3[] = {5, 4, 3, 2, 1, 0};

    int array4[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};
    int array5[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};
    int array6[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};

    int array7[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int array8[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int array9[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    size = sizeof(array5)/ sizeof(array5[0]);
    int *x = malloc(sizeof(int));


    printf("\n\n");
    //bubblesort(array2, size);
    printf("\n");
    Quicksort(array5, 0, size-1);
    printall(array5, size);
    //selectionsort(array4, size);
    push(8);
    push(33);
    printf(" %d", pop());


    printf("\n");
    int size1 = sizeof(d) / sizeof(d[0]) -1;

    updatematrix();
    int result = matrixmemo(1, size1); // Start the memoization
    printf("Minimum number of multiplications is %d\n", result);

    int res = HanoiMemo(20, 1, 2, 3);
    printf("HANOI %d\n", res);

    int size3 = sizeof(str1)/sizeof(char)-2;
    int size4 = sizeof(str2)/sizeof(char)-2;
    int result1 = LCSmemo(size3, size4);

    printf("LCS %d\n", result1);
    printLCS(size3, size4);
    return 0;


}
