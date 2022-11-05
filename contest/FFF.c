#include <stdio.h>
#include <string.h>
int main() {
    int T;
    char a[105][1005] = {'\0'};
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%s", a[i]);
    }
    for (int i = 0; i < T; i++) {
        for (int j = strlen(a[i]) - 1; j >= 0; j--) {
            if (a[i][j] != '*')
                putchar(a[i][j]);
        }
        putchar('\n');
    }
    return 0;
}