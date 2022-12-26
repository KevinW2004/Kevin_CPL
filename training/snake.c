#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 10

// 定义枚举类型来表示贪吃蛇的方向
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

// 定义结构体来表示贪吃蛇的身体
typedef struct {
    int x;
    int y;
} SnakePart;

// 定义结构体来表示贪吃蛇
typedef struct {
    SnakePart parts[100];
    int length;
    Direction dir;
} Snake;
// 定义结构体来表示食物
typedef struct {
    int x;
    int y;
} Food;

// 定义一个游戏板
char board[BOARD_HEIGHT][BOARD_WIDTH];

// 定义贪吃蛇和食物
Snake snake;
Food food;

// 初始化游戏板
void initBoard() {
    // 清空游戏板
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
        }
    }

    // 绘制游戏板边框
    for (int i = 0; i < BOARD_WIDTH; i++) {
        board[0][i] = '#';
        board[BOARD_HEIGHT - 1][i] = '#';
    }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board[i][0] = '#';
        board[i][BOARD_WIDTH - 1] = '#';
    }
}

// 初始化贪吃蛇
void initSnake() {
    // 设置贪吃蛇的起始位置
    snake.parts[0].x = BOARD_WIDTH / 2;
    snake.parts[0].y = BOARD_HEIGHT / 2;

    // 设置贪吃蛇的长度和方向
    snake.length = 1;
    snake.dir = RIGHT;
}

// 初始化食物
void initFood() {
    // 随机生成食物的位置
    food.x = rand() % (BOARD_WIDTH - 2) + 1;
    food.y = rand() % (BOARD_HEIGHT - 2) + 1;
}

// 绘制游戏板
void drawBoard() {
    // 清屏
    system("clear");

    // 遍历游戏板，绘制贪吃蛇和食物
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (i == food.y && j == food.x) {
                printf("$");
            } else {
                int snakePartFound = 0;
                for (int k = 0; k < snake.length; k++) {
                    if (i == snake.parts[k].y && j == snake.parts[k].x) {
                        printf("*");
                        snakePartFound = 1;
                        break;
                    }
                }
                if (!snakePartFound) {
                    printf("%c", board[i][j]);
                }
            }
        }
        printf("\n");
    }
}

// 获取按键输入
int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

// 处理按键输入
void handleInput() {
    int ch = getch();
    switch (ch) {
        case 'w':
            if (snake.dir != DOWN) {
                snake.dir = UP;
            }
            break;
        case 's':
            if (snake.dir != UP) {
                snake.dir = DOWN;
            }
            break;
        case 'a':
            if (snake.dir != RIGHT) {
                snake.dir = LEFT;
            }
            break;
        case 'd':
            if (snake.dir != LEFT) {
                snake.dir = RIGHT;
            }
            break;
        default:
            break;
    }
}

// 更新游戏状态
void update() {
    // 根据贪吃蛇的方向更新贪吃蛇的位置
    SnakePart nextPart;
    switch (snake.dir) {
        case UP:
            nextPart.x = snake.parts[0].x;
            nextPart.y = snake.parts[0].y - 1;
            break;
        case DOWN:
            nextPart.x = snake.parts[0].x;
            nextPart.y = snake.parts[0].y + 1;
            break;
        case LEFT:
            nextPart.x = snake.parts[0].x - 1;
            nextPart.y = snake.parts[0].y;
            break;
        case RIGHT:
            nextPart.x = snake.parts[0].x + 1;
            nextPart.y = snake.parts[0].y;
            break;
        default:
            break;
    }

    // 将贪吃蛇身体移动到下一个位置
    for (int i = snake.length - 1; i >= 1; i--) {
        snake.parts[i] = snake.parts[i - 1];
    }
    snake.parts[0] = nextPart;

    // 如果贪吃蛇头部碰到了食物，则增加贪吃蛇的长度
    if (nextPart.x == food.x && nextPart.y == food.y) {
        snake.length++;
        initFood();
    }

    // 如果贪吃蛇撞墙或者撞到自己，则游戏结束
    if (nextPart.x == 0 || nextPart.x == BOARD_WIDTH - 1 || nextPart.y == 0 ||
        nextPart.y == BOARD_HEIGHT - 1) {
        printf("游戏结束！\n");
        exit(0);
    }
    for (int i = 1; i < snake.length; i++) {
        if (nextPart.x == snake.parts[i].x && nextPart.y == snake.parts[i].y) {
            printf("游戏结束！\n");
            exit(0);
        }
    }
}

int main(int argc, char const* argv[]) {
    // 初始化随机数种子
    srand(time(0));

    // 初始化游戏板、贪吃蛇和食物
    initBoard();
    initSnake();
    initFood();

    // 设置按键非阻塞
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    // 游戏主循环
    while (1) {
        // 处理按键输入
        handleInput();

        // 更新游戏状态
        update();

        // 绘制游戏板
        drawBoard();

        // 休眠 100 毫秒
        usleep(100000);
    }

    return 0;
}
