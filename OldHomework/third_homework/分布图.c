#include <stdio.h>
#define SIZE 2000
char ans[SIZE][SIZE];
int max_y = 1;

void cramming(int x, int quantity) {  //画图
    int y;
    for (y = 2; y < 2 + quantity; y++) {
        ans[x][y] = '=';
    }
    if (y - 1 > max_y) {
        max_y = y - 1;
    }
}

int main() {
    int x = 0, n, flag;
    char a[1001];
    int lowerCount[26] = {0}, upperCount[26] = {0};
    scanf("%d", &n);
    scanf("%s", a);
    for (int i = 0; i < SIZE; i++) {  //初始化ans
        for (int j = 0; j < SIZE; j++) {
            ans[i][j] = ' ';
        }
    }

    for (int i = 0; i < n; i++) {  //桶计数
        if ('a' <= a[i] && a[i] <= 'z') {
            lowerCount[a[i] - 'a']++;
        }
        if ('A' <= a[i] && a[i] <= 'Z') {
            upperCount[a[i] - 'A']++;
        }
    }

    for (int i = 0; i < 26; i++) {  //制表
        flag = 0;
        if (lowerCount[i] != 0) {
            ans[x][0] = i + 'a';
            cramming(x, lowerCount[i]);
            x++;
            flag = 1;
        }
        if (upperCount[i] != 0) {
            ans[x][0] = i + 'A';
            cramming(x, upperCount[i]);
            x++;
            flag = 1;
        }
        if (flag) {
            x++;
        }
    }

    for (int temp_x = 0; temp_x < x - 1; temp_x++) {  //分割线
        ans[temp_x][1] = '-';
    }

    for (int y = max_y; y >= 0; y--) {  //输出
        for (int temp_x = 0; temp_x < x; temp_x++) {
            putchar(ans[temp_x][y]);
        }
        putchar('\n');
    }

    return 0;
}