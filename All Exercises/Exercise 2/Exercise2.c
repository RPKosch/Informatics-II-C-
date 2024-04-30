#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int TowerofHanoi(int disk, char A, char B, char C) {
    if (disk == 0) {
        return 0;
    } else {
        int moves = TowerofHanoi(disk - 1, A, C, B);
        printf("Move disk %d from %c to %c\n", disk, A, C);
        moves += 1;
        moves += TowerofHanoi(disk - 1, B, A, C);
        return moves;

//        A, B, C Swap B and C ->
//        A, B, C Swap A and B ->

    }
}

static int MemmoTowerofHanoi(int array[], int disk, char A, char B, char C) {
    if (disk == 1) {
        printf("Move disk %d from %c to %c\n", disk, A, C);
        return 1;
    }else if(array[disk] != 0){
        return array[disk];
    } else {
        array[disk-1] = TowerofHanoi(disk - 1, A, C, B);
        printf("Move disk %d from %c to %c\n", disk, A, C);
        array[disk-1] = TowerofHanoi(disk - 1, B, A, C);
        return array[disk-1]*2 + 1;

//        A, B, C Swap B and C ->
//        A, B, C Swap A and B ->

    }
}

double parseDouble(char expr[], int h, int t){
    int res = 0;
    for(int i = h; i <= t; i++){
        res = res*10 + (expr[i] - '0');
    }
    return (double) res;
}


static void bubblesort(int array[], int length){
    for(int i = length-1; i>=1; i--){
        for(int j = 1; j <= i; j++){
            if(array[j] < array[j-1]){
                int t = array[j];
                array[j] = array[j-1];
                array[j-1] = t;
            }
        }
    }
}

static void insertionsort(int array[], int length){
    for(int i = 1; i<length; i++){
        int j = i -1;
        int t = array[i];
        while(j>=0 && t < array[j]){
            array[j+1] = array[j];
            j--;
            }
        array[j+1] = t;
        }
}

static void selectionsort(int array[], int length){
    for(int i = 0; i <= length-2; i++){
        int k = i;
        for(int j = i+1; j <= length-1; j++){
            if(array[j] < array[k]){
                k = j;
            }
        }
        int t = array[i];
        array[i] = array[k];
        array[k] = t;
    }
}



static void printarray(int array[], int length){
    if(length == 0){
        printf("[]");
        return;
    }
    if(length == 1){
        printf("[%d]", array[length-1]);
        return;
    }
    printf("[");
    for(int i = 0; i < length-1; i++){
        printf("%d, ", array[i]);
    }
    printf("%d]\n", array[length-1]);
}

static int linearsearch(int array[], int length, int find){
    for(int i = 0; i < length; i++){
        if(array[i] == find){
            return i;
        }
    }
    return -1;
}

static int Binaraysearch(int array[], int length, int find){
    int l = 0;
    int r = length-1;

    int m = (l+r)/2;

    while (l <= r && array[m] != find){
        if(find < array[m]){
            r = m-1;
        } else {
            l = m+1;
        }
    }
    if (l<=r){
        return m;
    } else{
        return -1;
    }
}

static void getmiddle(int a, int b){
    int mid = (a-b)/2 + b;
    printf("\n mid: %d", mid);
}

int main(){
    int x = 88;
//    int total_moves = TowerofHanoi(20, 'A', 'B', 'C');
    int array[25];
    int total_moves1 = TowerofHanoi(3, 'A', 'B', 'C');
    printf("Total number of moves: %d\n", total_moves1);
    int newarray[] = {6, 3, 9, 1, 2, 6, 9, 33, 5, 8};
    int length = sizeof(newarray)/sizeof(newarray[0]);
    printarray(newarray, length);
    selectionsort(newarray, length);
    printarray(newarray, length);
    char hey[] = "5/88";
    printf("parse double %f", parseDouble(hey, 0, 4));
    char su[] = "heyho";
    printf("\n%d", sizeof(su));
    getmiddle(4, 8);
    getmiddle(4, 9);
    getmiddle(4, 7);
}
