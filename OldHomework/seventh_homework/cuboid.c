#include <stdio.h>
#define SIZE 100
/**mode 1:+-+ ;; mode 2: | | ;; mode 3: / / ;;
 * mode 4: + ;; mode 5: /|/ ;; mode 6: |/|   */
void putLine(char* ans, int x, int y, int len, int mode) {
    int flag = 0;
    switch (mode) {
        case 1:
            *(ans + y * SIZE + x) = '+';
            for (int cur_x = x + 1; cur_x <= x + len * 2; cur_x += 2) {
                *(ans + y * SIZE + cur_x) = '-';
                *(ans + y * SIZE + cur_x + 1) = '+';
            }
            break;
        case 2:
            for (int cur_x = x; cur_x <= x + len * 2; cur_x += 2) {
                *(ans + y * SIZE + cur_x) = '|';
            }
            break;
        case 3:
            for (int cur_x = x; cur_x <= x + len * 2; cur_x += 2) {
                *(ans + y * SIZE + cur_x) = '/';
            }
            break;
        case 4:
            for (int cur_x = x; cur_x < x + len; cur_x++) {
                *(ans + y * SIZE + cur_x) = flag ? '+' : ' ';
                flag = 1 - flag;
            }
            break;
        case 5:
            for (int cur_x = x; cur_x < x + len; cur_x++) {
                *(ans + y * SIZE + cur_x) = flag ? '|' : '/';
                flag = 1 - flag;
            }
            break;
        case 6:
            for (int cur_x = x; cur_x < x + len; cur_x++) {
                *(ans + y * SIZE + cur_x) = flag ? '/' : '|';
                flag = 1 - flag;
            }
            break;
    }
}
void paint(int a, int b, int c) {
    char ans[SIZE][SIZE] = {'\0'};
    int max_x = 2 * a;
    for (int y = 0; y <= c * 2 + b * 2; y++) {
        if (y <= c * 2) {
            if (y % 2 == 0) {
                putLine(ans[0], 0, y, a, 1);
                putLine(ans[0], 2 * a + 1, y, y, 4);
            } else {
                putLine(ans[0], 0, y, a, 2);
                putLine(ans[0], 2 * a + 1, y, y, 5);
            }
        } else {
            if (y % 2 == 1) {
                putLine(ans[0], y - 2 * c, y, a, 3);
                putLine(ans[0], 2 * a + y - 2 * c + 1, y,
                        max_x - (2 * a + y - 2 * c), 6);
            } else {
                putLine(ans[0], y - 2 * c, y, a, 1);
                putLine(ans[0], 2 * a + y - 2 * c + 1, y,
                        max_x - (2 * a + y - 2 * c), 4);
            }
        }
        if (max_x < 2 * b + 2 * a)
            max_x++;
    }
    for (int y = c * 2 + b * 2; y >= 0; y--) {
        for (int x = 0; x <= max_x; x++) {
            putchar(ans[y][x] == '\0' ? ' ' : ans[y][x]);
        }
        putchar('\n');
    }
}
int main() {
    int T;
    int a[60], b[60], c[60];
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
    for (int i = 0; i < T; i++) {
        paint(a[i], b[i], c[i]);
    }
    return 0;
}