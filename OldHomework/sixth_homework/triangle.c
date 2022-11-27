#include <math.h>
#include <stdio.h>
char ans[2000][3000] = {'\0'};
void putTriangle(int n, int x, int y) {
    if (n == 1) {
        ans[y][x] = '/';
        ans[y][x + 1] = '\\';
        ans[y + 1][x - 1] = '/';
        ans[y + 1][x] = '_';
        ans[y + 1][x + 1] = '_';
        ans[y + 1][x + 2] = '\\';
    } else {
        putTriangle(n - 1, x, y);
        putTriangle(n - 1, x - (int)pow(2, n - 1), y + (int)pow(2, n - 1));
        putTriangle(n - 1, x + (int)pow(2, n - 1), y + (int)pow(2, n - 1));
    }
}
int main() {
    int n;  // height = 2^n ;; width=2^(n+1)
    scanf("%d", &n);
    putTriangle(n, (int)pow(2, n) - 1, 0);
    for (int y = 0; y < (int)pow(2, n); y++) {
        for (int x = 0; x < (int)pow(2, n + 1); x++) {
            if (ans[y][x] != '\0')
                putchar(ans[y][x]);
            else
                putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}