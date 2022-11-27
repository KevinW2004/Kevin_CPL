#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char* s;
    s = (char*)malloc(4096);
    fgets(s, 4096, stdin);
    for (int i = 0; i < strlen(s); i++) {
        if (i == 0 || *(s + i - 1) == ' ') {
            putchar(toupper(*(s + i)));
        } else {
            putchar(tolower(*(s + i)));
        }
    }
    return 0;
}