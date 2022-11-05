#include <stdio.h>
char a[200][200] = {'\0'};
char neighbor(int i, int j) {
    int vectors[8][2] = {{0, 1}, {0, -1}, {1, 0},  {-1, 0},
                         {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int count = 0;
    for (int k = 0; k < 8; ++k) {
        int newI = i + vectors[k][0];
        int newJ = j + vectors[k][1];
        if (a[newI][newJ] == '*') {
            count++;
        }
    }
    return count + '0';
}
int main() {
    int n;
    scanf("%d", &n);
    getchar();
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            a[row][col] = getchar();
        }
        getchar();
    }
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            if (a[row][col] != '*')
                a[row][col] = neighbor(row, col);
            putchar(a[row][col]);
        }
        putchar('\n');
    }
    return 0;
}