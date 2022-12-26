#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义棋盘大小
#define ROW 10
#define COL 10

// 定义棋盘数组
int board[ROW][COL] = {0};

// 定义骰子点数数组
int dice[4] = {0, 1, 2, 3};

// 定义游戏函数
void play() {
    // 定义当前玩家和棋子位置
    int player = 1;
    int x = 0, y = 0;

    // 循环执行游戏操作
    while (1) {
        // 显示棋盘
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }

        // 打乱骰子顺序
        shuffle(dice);

        // 显示骰子点数
        printf("Player %d, you rolled a %d, %d, %d, and %d.\n", player, dice[0],
               dice[1], dice[2], dice[3]);

        // 输入棋子位置
        printf("Player %d, please enter the position of your piece: ", player);
        scanf("%d%d", &x, &y);

        // 检查棋子位置是否有效
        if (x >= 0 && x < ROW && y >= 0 && y < COL && board[x][y] == player) {
            // 在棋盘上移动
            // 移动棋子
            for (int i = 0; i < 4; i++) {
                int dx = x + dice[i];
                int dy = y + dice[i];
                if (dx >= 0 && dx < ROW && dy >= 0 && dy < COL &&
                    board[dx][dy] == 0) {
                    board[dx][dy] = player;
                    board[x][y] = 0;
                    x = dx;
                    y = dy;
                }
            }

            // 判断游戏是否结束
            if (checkWin(player)) {
                printf("Player %d wins!\n", player);
                break;
            }

            // 切换玩家
            player = player % 2 + 1;
        } else {
            printf("Invalid position, please try again.\n");
        }
    }
}

// 定义打乱骰子顺序的函数
void shuffle(int* dice) {
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int temp = dice[i];
        dice[i] = dice[j];
        dice[j] = temp;
    }
}

// 定义判断胜负的函数
int checkWin(int player) {
    // 判断是否到达终点
    int x = 0, y = 0;
    if (player == 1) {
        x = ROW - 1;
        y = COL - 1;
    }
    if (board[x][y] == player) {
        return 1;
    }

    return 0;
}

// 主函数
int main() {
    // 初始化棋盘
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = 0;
        }
    }
    board[0][0] = 1;
    board[ROW - 1][COL - 1] = 2;

    // 执行游戏
    play();

    return 0;
}
