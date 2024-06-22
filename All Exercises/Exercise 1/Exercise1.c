#include <stdio.h>
#include <string.h>

//Exercise 1.1

static void snippet1() {
    // 2147483647, -2147483648, -2147483647
    // Size of Int is reached -> starts again with 0..00 (32-bit)
    int a = 2147483647;
    int b = 2147483648;
    int c = 2147483649;
    printf("%d, %d, %d", a, b, c);
}

static void snippet2() {
    // Random Elements
    // Accessing its elements in the loop leads to reading uninitialized values, resulting in undefined behavior.
    int myArray[20];
    for (int i = 0; i < 20; i++) {
        printf("%d \n", myArray[i]);
    }
}

static void snippet3() {
    // Size is not right
    // Could result in an error
    int myArray[1];
    myArray[0] = 0;
    myArray[1] = 1;
    myArray[2] = 2;
    printf("%d, %d, %d", myArray[0], myArray[1], myArray[2]);
}

static void snippet4() {
    // first prints numbers then "hello World"
    // Numbers with c are changed to ascii
    int myArray[] = {72, 101, 108, 108, 111, 32,
                     87, 111, 114, 108, 100, 33};
    for (int i = 0; i < 12; i++) {
        printf("%d", myArray[i]);
    }
    printf("\n");
    for (int i = 0; i < 12; i++) {
        printf("%c", myArray[i]);
    }
}

static void snippet5() {
    // how we find length of array
    // indexes go only to n-1
    int myArray[10];
    int size1 = sizeof(myArray);
    int size2 = sizeof(myArray[0]);
    int size3 = size1 / size2;
    printf("%d, %d, %d", size1, size2, size3);
}

static void snippet6() {
    // prints length 6 because of the null in the end of the string
    // use the strlen function from the <string.h> library.
    char myString[] = "hello";
    int stringSize = sizeof(myString) / sizeof(myString[0]);
    printf("\n%d, ", stringSize);
    for (int i = 0; i < stringSize; i++) {
        printf("%c", myString[i]);
    }
}

//Exercise 1.2

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

static void rleCompression(char string[], int length){
    char newstring[length*2];
    for(int x = 0; x < length; x++){
        int count = 1;
        while(x < length -1 && string[x] == string[x+1]){
            x++;
            count++;
        }
        sprintf(newstring, "%s%d%c", newstring, count ,string[x]);
    }
    printf("%s", newstring);
}

//Exercise 1.4

static void getcontinousSubarrays(int arrays[], int length){
    for(int curlen=1; curlen <= length; curlen++){
        for(int start = 0; start <= length - curlen; start++){
            printf("\n[");
            for(int x = start; x < curlen + start; x++){
                printf("%d ", arrays[x]);
            }
            printf("]");
        }
    }
}

static void getcontinousSubarraystozero(int arrays[], int length){
    for(int curlen=1; curlen <= length; curlen++){
        for(int start = 0; start <= length - curlen; start++){
            int sum = 0;
            for(int x = start; x < curlen + start; x++){
                sum += arrays[x];
            }
            if(sum == 0){
                printf("True\n");
                return;
            }
        }
    }
    printf("False\n");
    return;
}

static void bubblesort(int array[], int length){
    printall(array, length);
    for(int x = length; x > 0; x--){
        for(int y = 1; y < x; y++ ){
            if(array[y] < array[y-1]){
                swapint(array, y, y-1);
            }
        }
    }
    printall(array, length);
}
// Correct sorted list until iteration from left
static void insertionsort(int array[], int length){
    int count = 0;
    for(int i = 1; i <= length-1; i++){
        int j = i -1;
        int t = array[i];
         while(j>=0 && t < array[j]){
                    count++;
                    array[j+1] = array[j];
                    j--;
                }
                array[j+1] = t;

}
// Correct element form left to right
static void selectionsort(int array[], int length){
    int count = 0;
    for(int i = 0; i <= length-2; i++){
        int k = i;
        for(int j = i+1; j <= length-1; j++){
            count++;
            if(array[j]<array[k]){
                k = j;
            }
        }
        int t = array[i];
        array[i] = array[k];
        array[k] = t;

        printf("[");
        for(int x = 0; x < length; x++){
            printf(" %d", array[x]);
        }
        printf(" ]\n");
    }
    printf("%d", count);
}

static void swapchar(char list[], int first, int second){
    char tmp = list[first];
    list[first] = list[second];
    list[second] = tmp;
}

int main() {
    char string[] = "hallllloo";
    int size = strlen(string);
    rleCompression(string, size);

    int array1[] = {5, 4, 3, 2, 1, 0};
    int array2[] = {5, 4, 3, 2, 1, 0};
    int array3[] = {5, 4, 3, 2, 1, 0};

    int array4[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};
    int array5[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};
    int array6[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};

    int array7[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int array8[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int array9[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    size = sizeof(array2)/ sizeof(array2[0]);
    getcontinousSubarrays(array2, size);
    printf("\n\n");
    bubblesort(array2, size);
//    printf("\n");
//    insertionsort(array3, size);
//    printf("\n");
//    selectionsort(array4, size);

    char string1[] = "Gugus";
    int sl = sizeof(string1)/ sizeof(string1[0]);
    printf("\n %s", string1);
    swapchar(string1, 0, sl-2);
    printf("\n %s", string1);
    return 0;


}
