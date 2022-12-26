#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#define BLACK '#'
#define WHITE '*'
char board[N][N];
short vec[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
short black_win = 0;
bool isEdge(int y, int x) {
    if (y >= 0 && y < N && x >= 0 && x < N)
        return false;
    return true;
}
bool isWin(char cur_board[][N], char color) {
    for (int y0 = 0; y0 < N; y0++)
        for (int x0 = 0; x0 < N; x0++) {
            if (cur_board[y0][x0] != color)
                continue;
            for (int v = 0; v < 4; v++) {
                int cnt = 0, x = x0, y = y0;
                while (cur_board[y][x] == cur_board[y0][x0] && !isEdge(y, x)) {
                    cnt++;
                    y += vec[v][0];
                    x += vec[v][1];
                }
                if (cnt >= 5)
                    return true;
            }
        }
    return false;
}
void Judge(char color) {
    char new_board[N][N];
    for (int y0 = 0; y0 < N; y0++)
        for (int x0 = 0; x0 < N; x0++) {
            if (board[y0][x0] == '_') {
                memcpy(new_board, board, sizeof(board));
                new_board[y0][x0] = color;
                if (isWin(new_board, color)) {
                    if (color == '*') {
                        printf("Lose\n");
                        black_win = -1;
                        return;
                    } else {
                        black_win++;
                        if (black_win >= 2) {
                            printf("Win\n");
                            return;
                        }
                    }
                }
            }
        }
}
int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        black_win = 0;
        for (int i = 0; i < N; i++)
            scanf("%s", board[i]);
        Judge('*');
        if (black_win >= 0)
            Judge('#');
        if (black_win == 0 || black_win == 1)
            printf("Not Sure\n");
    }
    return 0;
}