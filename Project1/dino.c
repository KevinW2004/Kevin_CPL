#include <conio.h>  // gotoxy()
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  //sleep(ms)
#define scrX 100
#define scrY 30
void WinSet(int w, int h) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); /*标准输出句柄*/
    COORD size = {w, h};                           /*窗口大小*/
    SMALL_RECT rc = {0, 0, w - 1, h - 1};  //要设置的窗口显示的大小和位置
    CONSOLE_CURSOR_INFO cursor = {1, FALSE}; /*光标信息，用于隐藏光标*/
    SetConsoleWindowInfo(hOut, TRUE, &rc);
    SetConsoleScreenBufferSize(hOut, size);
    SetConsoleCursorInfo(hOut, &cursor);
    system("cls");
    return;
}
void gotoxy(short x, short y) {  //控制台窗口光标定位
    static COORD crd;  //定义 COORD 类型(窗口坐标)的静态局部变量 crd
    crd.X = x;
    crd.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}
char scr[scrY][scrX];
bool Lose = false;
char shape[3][8][12] = {
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
struct {
    int state;
    int x;
    int y;
} dino;  // x,y 表示恐龙左上角
void PrintScr() {
    for (int i = 0; i < scrY; i++, printf("\n"))
        for (int j = 0; j < scrX; j++)
            printf("%c", scr[i][j]);
}
void Initialize() {
    memset(scr, ' ', sizeof(scr));
    for (int i = 0; i < scrX; i++) {
        scr[scrY - 1][i] = '=';
        scr[0][i] = '-';
    }
    for (int i = 1; i < scrY - 1; i++) {
        scr[i][0] = '|';
        scr[i][scrX - 1] = '|';
    }
    dino.state = 0;
    dino.x = 3;
    dino.y = scrY - 9;
    WinSet(scrX, scrY + 3);
    ShowCursor(false);
    PrintScr();
}
void drawDino() {
    for (int i = 0; i < 8; i++) {  // y
        gotoxy(dino.x, i + dino.y);
        for (int j = 0; j < 12; j++) {
            putchar(shape[dino.state][i][j]);
        }
    }
    dino.state = (dino.state + 1) % 3;
}

int main() {
    Initialize();
    SetConsoleOutputCP(437);
    int num = 10;
    for (int i = 0; i < num; i++) {
        drawDino();
        Sleep(1000);
    }
    return 0;
}