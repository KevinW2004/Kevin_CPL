#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int Judge(char* s, char* t, int len, int start) {
    for (int i = start; i < start + len; i++) {
        if (*(s + i) != *(t + (i - start))) {
            return 0;
        }
    }
    return 1;
}
int main() {
    char *s, *t;
    s = (char*)malloc(sizeof(char) * 100005);
    t = (char*)malloc(sizeof(char) * 100005);
    scanf("%s%s", s, t);
    int lens = strlen(s);
    int lent = strlen(t);
    for (int i = 0; i <= lens - lent; i++) {
        if (Judge(s, t, lent, i)) {
            printf("%d ", i);
        }
    }
    return 0;
}