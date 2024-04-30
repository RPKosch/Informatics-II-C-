#include <stdio.h>
#include <math.h>
void printsubstring(char string[]){
    printf("%s\n", string);
}

int getlongestsubsequence(char s1[], char s2[], int l1, int l2, char cursub[], int cur){
    if(l1 == 0 || l2 == 0){
        cursub[cur] = '\0'; // Terminate the string
        printsubstring(cursub);
        return 0;
    }
    if (s1[l1-1] == s2[l2-1]){
        cursub[cur] = s1[l1-1];
        return 1 + getlongestsubsequence(s1, s2, l1-1, l2-1, cursub, cur+1);
    }
    return fmax(getlongestsubsequence(s1, s2, l1-1, l2, cursub, 0), getlongestsubsequence(s1, s2, l1, l2-1, cursub, 0));
}

int main(){
    printf("Checking\n");
    char s1[] = "GGTTCAT";
    char s2[] = "GTATCT";

    int l1 = sizeof(s1) / sizeof(s1[0]) - 1; // Calculate the length of s1
    int l2 = sizeof(s2) / sizeof(s2[0]) - 1; // Calculate the length of s2

    char end[10];
    //int x = getlongestsubsequence(s1, s2, l1, l2, end, 0);
    char array[] = "hallo";
    int size = sizeof(array)/sizeof(array[0]);
    printf("Solution: %d\n", size);
    printf("%d", array[3]);
    return 0;
}