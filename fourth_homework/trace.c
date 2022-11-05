#include <stdio.h>
int vis[60][60] = {0};  // 1 is visited
char board[60][60] = {'\0'};
int x0, yO;
int ans = 0;
int searchNext(int x, int y) {  // 1 means finding the next place
    int flag = 0;
    int vector[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    for (int k = 0; k < 4; ++k) {
        int new_x = x + vector[k][0];
        int new_y = y + vector[k][1];
        if (board[new_y][new_x] == '#' && vis[new_y][new_x] == 0) {
            x0 = new_x;
            yO = new_y;
            vis[yO][x0] = 1;
            flag = 1;
            break;
        }
    }
    return flag;
}
int main() {
    int n, m;
    scanf("%d %d %d %d", &n, &m, &yO, &x0);
    vis[yO][x0] = 1;
    for (int y = 1; y <= n; y++) {
        getchar();
        for (int x = 1; x <= m; x++) {
            board[y][x] = getchar();
            if (board[y][x] == '#')
                ans++;
        }
    }
    printf("%d\n", ans);
    do {
        printf("%d %d\n", yO, x0);
    } while (searchNext(x0, yO));
    return 0;
}