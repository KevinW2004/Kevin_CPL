#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define scrX 100
#define scrY 25
#define MAX_BLOCKS 6  // 地图上同时最多的障碍物数量
/* 以下两个函数来源于自行进行网络信息学习后自行得出,为windows窗口操控必需 */
void WinSet(int w, int h) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  // 标准输出句柄
    COORD size = {w, h};                            // 窗口大小
    SMALL_RECT rc = {0, 0, w - 1, h - 1};  // 要设置的窗口显示的大小和位置
    CONSOLE_CURSOR_INFO cursor = {1, FALSE};  // 隐藏光标
    SetConsoleWindowInfo(hOut, TRUE, &rc);
    SetConsoleScreenBufferSize(hOut, size);
    SetConsoleCursorInfo(hOut, &cursor);
    system("cls");
    SetConsoleOutputCP(437);  // 扩展ascii码标准
}
void gotoxy(short x, short y) {  // 控制台窗口光标定位
    static COORD crd;            // COORD 类型(窗口坐标)
    crd.X = x;
    crd.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}
/* 以下为必备全局变量 */
char scr[scrY][scrX];
bool Lose = false;
int score;
char dino_normal[3][8][12] = {
    //[state][y][x]
    // 0=站着; 1=抬左脚；2=抬右脚
    {{32, 32, 32, 32, 32, 32, 95, 95, 95, 95, 95, 32},
     {32, 32, 32, 32, 206, 181, 32, 64, 32, 32, 32, 179},
     {32, 179, 32, 32, 206, 181, 32, 32, 32, 200, 205, 181},
     {47, 179, 32, 32, 206, 181, 32, 32, 32, 218, 196, 217},
     {92, 192, 208, 208, 208, 217, 32, 32, 32, 198, 203, 187},
     {32, 92, 95, 95, 95, 95, 95, 95, 47, 32, 32, 32},
     {32, 32, 32, 32, 179, 32, 32, 179, 32, 32, 32, 32},
     {32, 32, 32, 32, 207, 205, 32, 207, 205, 32, 32, 32}},
    {{32, 32, 32, 32, 32, 32, 95, 95, 95, 95, 95, 32},
     {32, 32, 32, 32, 206, 181, 32, 64, 32, 32, 32, 179},
     {32, 179, 32, 32, 206, 181, 32, 32, 32, 200, 205, 181},
     {47, 179, 32, 32, 206, 181, 32, 32, 32, 218, 196, 217},
     {92, 192, 208, 208, 208, 217, 32, 32, 32, 198, 203, 187},
     {32, 92, 95, 95, 95, 95, 95, 95, 47, 32, 32, 32},
     {32, 32, 32, 32, 207, 205, 32, 179, 32, 32, 32, 32},
     {32, 32, 32, 32, 32, 32, 32, 207, 205, 32, 32, 32}},
    {{32, 32, 32, 32, 32, 32, 95, 95, 95, 95, 95, 32},
     {32, 32, 32, 32, 206, 181, 32, 64, 32, 32, 32, 179},
     {32, 179, 32, 32, 206, 181, 32, 32, 32, 200, 205, 181},
     {47, 179, 32, 32, 206, 181, 32, 32, 32, 218, 196, 217},
     {92, 192, 208, 208, 208, 217, 32, 32, 32, 198, 203, 187},
     {32, 92, 95, 95, 95, 95, 95, 95, 47, 32, 32, 32},
     {32, 32, 32, 32, 179, 32, 32, 207, 205, 32, 32, 32},
     {32, 32, 32, 32, 207, 205, 32, 32, 32, 32, 32, 32}},
};
char dino_crouch[4][12] = {
    {32, 32, 32, 32, 32, 32, 95, 95, 95, 95, 95, 32},
    {47, 179, 32, 32, 206, 181, 32, 64, 32, 218, 196, 217},
    {92, 192, 208, 208, 208, 217, 32, 32, 32, 198, 203, 187},
    {32, 32, 32, 32, 207, 205, 32, 207, 205, 32, 32, 32}};
struct {
    int state;
    int x;
    int y;
    short jump_time;
    short crouch_time;
    short invincible_time;
} dino;                 // x,y 表示恐龙左上角
typedef struct block {  // 障碍物链表，不使用头指针
    int x;
    int h;
    struct block* next;
    short kind;  // 0=仙人掌；1=鸟
} block;
block* blocks_head = NULL;
int number_blocks = 0;
struct {
    int x;
    int y;
    short kind;  // 0为金币，1为无敌
} item;

/* 以下为基本函数 */
void PrintScr() {
    for (int i = 0; i < scrY; i++, printf("\n"))
        for (int j = 0; j < scrX; j++)
            printf("%c", scr[i][j]);
}
void Initialize() {
    // Initialize the scr[][]
    memset(scr, ' ', sizeof(scr));
    for (int i = 0; i < scrX; i++) {
        scr[scrY - 1][i] = '=';
        scr[0][i] = '-';
    }
    for (int i = 1; i < scrY - 1; i++) {
        scr[i][0] = '|';
        scr[i][scrX - 1] = '|';
    }
    // Initialize the dino
    dino.state = 0;
    dino.x = 3;
    dino.y = scrY - 9;
    dino.jump_time = 0;
    dino.crouch_time = 0;
    dino.invincible_time = 0;
    // Initialize the blocks
    srand(time(NULL));
    blocks_head = (block*)malloc(sizeof(block));
    blocks_head->next = NULL;
    blocks_head->x = -1;
    number_blocks = 0;
    Lose = false;
    // Initialize the item
    item.x = -1;
    // Initialize the screen
    WinSet(scrX, scrY + 3);
    ShowCursor(false);
    PrintScr();
    score = 0;
}
bool crash(int x, int y) {
    block* p = blocks_head;
    while ((p = p->next) != NULL) {
        if (x == p->x && ((y >= scrY - 1 - p->h && p->kind == 0) ||
                          (y == p->h && p->kind == 1)))
            return true;
    }
    return false;
}
void GotItem(int x, int y) {
    if (x == item.x && y == item.y) {
        gotoxy(x + 1, item.y);
        putchar(' ');
        switch (item.kind) {
            case 0:
                score += 50;
                item.x = -1;
                break;
            case 1:
                dino.invincible_time = 30;
                item.x = -1;
                break;
        }
    }
}
void drawDino() {             // 判断碰撞也糅合在这个函数
    if (!dino.crouch_time) {  // 正常状态，包括跑和跳
        for (int i = 0; i < 8; i++) {
            gotoxy(dino.x, i + dino.y);
            for (int j = 0; j < 12; j++) {
                putchar(dino_normal[dino.state][i][j]);
                if (dino_normal[dino.state][i][j] != 32) {
                    GotItem(dino.x + j, i + dino.y);
                    if (dino.invincible_time == 0)
                        Lose = Lose || crash(dino.x + j, dino.y + i);
                }
            }
        }
        dino.state = (dino.state + 1) % 3;
    } else {  // 蹲下
        for (int i = 0; i < 4; i++) {
            gotoxy(dino.x, i + dino.y);
            for (int j = 0; j < 12; j++) {
                putchar(dino_crouch[i][j]);
                if (dino_crouch[i][j] != 32) {
                    GotItem(dino.x + j, dino.y + i);
                    if (dino.invincible_time == 0)
                        Lose = Lose || crash(dino.x + j, dino.y + i);
                }
            }
        }
    }
}
void eraseDino() {
    for (int i = 0; i < (dino.crouch_time ? 4 : 8); i++) {
        gotoxy(dino.x, i + dino.y);
        for (int j = 0; j < 12; j++) {
            putchar(' ');
        }
    }
}
void jump() {  // 跳起最大高度为:8
    eraseDino();
    dino.jump_time--;
    if (dino.jump_time >= 1 && dino.jump_time <= 3) {
        dino.y += 2;
    } else if (dino.jump_time >= 4 && dino.jump_time <= 6) {
        dino.y += 1;
    } else if (dino.jump_time <= 10 && dino.jump_time >= 8) {
        dino.y -= 1;
    } else if (dino.jump_time <= 13 && dino.jump_time >= 11) {
        dino.y -= 2;
    }
}
void crouch() {
    eraseDino();
    dino.crouch_time--;
    if (dino.crouch_time)
        dino.y = scrY - 5;
    else
        dino.y = scrY - 9;
}
void PrintScore() {
    gotoxy(0, scrY);
    printf("Score: %d           $=50 score; %c=invincible", score, 237);
    if (dino.invincible_time > 0) {
        printf("\nInvincible Time: ");
        for (int i = 1; i <= 30; i++) {
            if (i <= dino.invincible_time)
                putchar(219);  // 黑色大方块表示时间条
            else
                putchar(' ');
        }
    } else {
        printf("\n                                         ");
    }
}
void CreateBlocks() {
    if (number_blocks < MAX_BLOCKS) {
        block* p = blocks_head;
        while (p->next != NULL)
            p = p->next;  // 此时p为链表尾
        if (number_blocks == 0 ||
            (rand() % 11 == 0 && p->x <= scrX - 30)) {  // 生成新的结点
            block* new = (block*)malloc(sizeof(block));
            new->kind = rand() % 2;  // 随机决定障碍物类型
            new->x = scrX - 4;
            if (new->kind == 0) {
                new->h = (rand() % 4) + 2;  // 仙人掌高度：2 到 5
            } else {
                new->h = (rand() % (scrY - 7)) + 5;  // 鸟的高度：5 到 scrY-3
            }
            new->next = p->next;
            p->next = new;
            number_blocks++;
        }
    }
    block* p = blocks_head;
    while ((p = p->next) != NULL) {
        if (p->kind == 0) {
            for (int hi = 1; hi <= p->h; hi++) {
                gotoxy(p->x, scrY - 1 - hi);
                printf("#  ");
            }
            (p->x) -= 2;
            if (p->x <= 0) {  // 删除走到头的仙人掌结点
                blocks_head->next = p->next;
                for (int hi = 1; hi <= p->h; hi++) {
                    gotoxy(p->x + 2, scrY - 1 - hi);
                    printf(" ");
                }
                number_blocks--;
            }
        } else {
            gotoxy(p->x, p->h);
            printf((p->x == scrX - 4) ? "##" : "##  ");
            (p->x) -= 2;
            if (p->x <= 0) {  // 删除走到头的鸟结点
                blocks_head->next = p->next;
                gotoxy(p->x + 2, p->h);
                printf("  ");
                number_blocks--;
            }
        }
    }
}
bool GameOver() {
    system("cls");
    printf(
        "Game Over!\n"
        "Your final score: %d \n"
        "Press 'a' to play again\n"
        "Press 'q' key to quit",
        score);
    char c = getch();
    while (c != 'a' && c != 'q')
        c = getch();
    switch (c) {
        case 'a':
            return true;
        case 'q':
            return false;
    }
}
void CreateItems() {
    if (item.x == -1 && (score % 200 == 0 || rand() % 97 == 0)) {  // 产生新道具
        item.kind = rand() % 2;
        item.x = scrX - 4;
        item.y = scrY - 2 - rand() % 16;
    }
    if (item.x > 0)
        switch (item.kind) {
            case 0:  // gold = 50 score
                gotoxy(item.x, item.y);
                printf("$ ");
                item.x--;
                if (item.x <= 2) {
                    gotoxy(item.x + 1, item.y);
                    putchar(' ');
                    item.x = -1;
                }
                break;
            case 1:  // invincible
                gotoxy(item.x, item.y);
                printf("%c ", 237);
                item.x--;
                if (item.x <= 2) {
                    gotoxy(item.x + 1, item.y);
                    putchar(' ');
                    item.x = -1;
                }
                break;
        }
}
/* 以下为main函数 */
int main() {
    system("cls");
    printf(
        "Welcome to \n***The Dino Run!***\n"
        "Made By 吴凯文 221250068\n"
        "You can press 'q' to pause or 'esc' to finish whenever you "
        "like.\n"
        "!!Please ensure that the size of your console windows is big "
        "enough!!\n"
        "Press any keys to start.\n");
    system("pause");
GameStart:
    Initialize();
    while (!Lose) {
        score++;
        fflush(stdin);        // 清空缓冲区
        rewind(stdin);        // 三条都是，不知道哪个能生效
        setbuf(stdin, NULL);  //
        if (kbhit()) {        // 读取输入
            char press = getch();
            if (press == 224)
                press = getch();
            switch (press) {
                case 'q':
                    getch();
                    break;
                case ' ':
                case 72:                    // 空格或者上方向键起跳
                    if (!dino.jump_time) {  // 本来就在跳了，禁止n段跳
                        dino.jump_time = 14;
                    }
                    if (dino.crouch_time) {  // 本来是蹲着的，先回复站姿
                        eraseDino();
                        dino.y = scrY - 9;
                        dino.crouch_time = 0;
                    }
                    break;
                case 80:                   // 下方向键下蹲
                    if (dino.jump_time) {  // 本来是在空中
                        dino.jump_time = 0;
                        eraseDino();
                    }
                    dino.crouch_time = 10;
                    break;
                case 27:  // esc
                    Lose = true;
                    break;
            }
        }
        if (dino.crouch_time)
            crouch();
        if (dino.jump_time)
            jump();
        PrintScore();
        CreateItems();
        CreateBlocks();
        drawDino();
        Sleep((100 - (score / 50)) >= 10 ? (100 - (score / 50)) : 0);
        if (dino.invincible_time > 0)
            dino.invincible_time--;
    }
    if (GameOver())
        goto GameStart;
    system("cls");
    return 0;
}