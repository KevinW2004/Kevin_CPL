#include <stdio.h>
#include <string.h>
char life[2000] = {'\0'}, new_life[2000] = {'\0'};
void copyStr(char* a, char* b, int as, int bs) {
    for (int i = 0; i < strlen(b) - bs; i++) {
        a[i + as] = b[i + bs];
    }
    return;
}
int findA(int x) {
    int count = 0;
    for (int i = x - 3; i <= x + 3; i++) {
        if (i == x)
            continue;
        else if (new_life[i] == 'A')
            count++;
    }
    return count;
}
int findB(int x) {
    int count = 0;
    for (int i = x - 3; i <= x + 3; i++) {
        if (i == x)
            continue;
        else if (new_life[i] == 'B')
            count++;
    }
    return count;
}
int main() {
    int rounds;
    scanf("%d", &rounds);
    scanf("%s", life);
    for (int n = 0; n < rounds; n++) {
        copyStr(new_life, life, 3, 0);
        for (int i = 3; i < strlen(life) + 3; i++) {
            switch (new_life[i]) {
                case 'A':
                    life[i - 3] = findB(i) || (findA(i) <= 1 || findA(i) >= 5)
                                      ? '.'
                                      : 'A';
                    break;
                case 'B':
                    life[i - 3] = findA(i) || (findB(i) <= 1 || findB(i) >= 5)
                                      ? '.'
                                      : 'B';
                    break;
                case '.':
                    if (findB(i) == 0 && (findA(i) <= 4 && findA(i) >= 2))
                        life[i - 3] = 'A';
                    else if (findA(i) == 0 && (findB(i) <= 4 && findB(i) >= 2))
                        life[i - 3] = 'B';
                    break;
            }
        }
    }

    printf("%s", life);
    return 0;
}
