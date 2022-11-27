#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1005
int findBias(char* s1, int len1, char* s2, int len2) {
    int bias = 0;
    for (int i = len1 - len2 > 0 ? len1 - len2 : 0; i < len1; i++) {
        for (int j = i; j < len1; j++, bias++) {
            if (*(s1 + j) != *(s2 + j - i)) {
                bias = 0;
                break;
            }
        }
        if (bias)
            break;
    }
    return bias;
}
int main() {
    int T, bias;
    char *s1, *s2;
    scanf("%d", &T);
    s1 = (char*)malloc(SIZE * 2);
    s2 = (char*)malloc(SIZE);
    for (int i = 0; i < T; i++) {
        scanf("%s%s", s1, s2);
        bias = findBias(s1, strlen(s1), s2, strlen(s2));
        printf("%s\n", strcat(s1, s2 + bias));
    }
    return 0;
}