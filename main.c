#include <stdio.h>

int main() {
    int myArray[] = {72, 101, 108, 108, 111, 32,
                     87, 111, 114, 108, 100, 33};
    for(int i = 0; i < 12; i++) {
        printf("%d", myArray[i]);
    }
    printf("\n");
    for(int i = 0; i < 12; i++) {
        printf("%c", myArray[i]);
    }
    return 0;
}
// 1.1 int goes backwards because that max of integer
// 1.2 Array is already loaded with differnt values
// 1.3 Nothing is printed - Array is to small
// 1.4
