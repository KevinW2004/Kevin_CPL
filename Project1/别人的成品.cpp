#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define N 80
#define up 72
#define left 75
#define right 77
#define down 80
void run();
void yn();
void print(int[][N]);
void menu();
int scr[22][N] = {0}, pl = 9, shit, width = 70, score = 0, death = 0,
    jump_time = 0, game_time = 0, day = 0, jump_height = 0, shift_time = 0;
int main() {
    menu();
    run();
}

void drawplayer(int a[][N], int xlu, int ylu) {  //画玩家
    for (int i = 1; i <= 3; i++)
        a[xlu][ylu + i] = 1;
    for (int i = 0; i <= 4; i++)
        a[xlu + 1][ylu + i] = 1;
    a[xlu + 2][ylu + 1] = 1;
    a[xlu + 2][ylu + 3] = 1;
}

bool search_player(int a[][N], int xlu, int ylu) {  //检测与障碍的碰撞
    for (int i = 1; i <= 3; i++)
        if (a[xlu][ylu + i] == 2 || a[xlu][ylu + i] == 3)
            return false;
    for (int i = 0; i <= 4; i++)
        if (a[xlu + 1][ylu + i] == 2 || a[xlu + 1][ylu + i] == 3)
            return false;
    if (a[xlu + 2][ylu + 1] == 2 || a[xlu + 2][ylu + 1] == 3)
        return false;
    if (a[xlu + 2][ylu + 3] == 2 || a[xlu + 2][ylu + 3] == 3)
        return false;
    return true;
}

void days(int q, int a[][N]) {  //太阳&月亮
    for (int i = 3; i <= 7; i++) {
        for (int j = 51; j <= 55; j++) {
            a[i][j] = 0;
        }
    }
    if (q == 1) {  //月亮，开启昼夜才有
        a[4][52] = 4;
        a[7][52] = 4;
        for (int i = 53; i <= 54; i++) {
            a[4][i] = 4;
            a[5][i] = 4;
            a[6][i] = 4;
            a[7][i] = 4;
        }
        a[4][54] = 0;
        a[7][54] = 0;
        a[5][55] = 4;
        a[6][55] = 4;
    } else {
        for (int i = 3; i <= 7; i++) {
            for (int j = 51; j <= 56; j++) {
                a[i][j] = 4;
            }
        }
        a[4][51] = 0;
        a[4][56] = 0;
        a[7][51] = 0;
        a[7][56] = 0;
    }
}

void print(int a[][N]) {  //绘图函数
    COORD c = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    int i, j;
    for (i = 4; i < 22; i++) {
        a[i][width - 1] = 4;
        for (j = 0; j < width; j++) {
            if (a[i][j] == 0) {
                printf(" ");
            }
            if (a[i][j] == 1)
                printf("@");
            if (a[i][j] == 2)
                printf("#");
            if (a[i][j] == 3)
                printf("<");
            if (a[i][j] == 4) {
                printf("*");
            }
            if (i == 4 && j == width - 1)
                printf("score:%d", score / 20);
            if (i == 5 && j == width - 1)
                printf("Press Esc to exit");
        }
        printf("\n");
    }
    for (j = 0; j < width; j++)
        printf("~");
}

void yn() {  //死亡界面
    system("cls");
    system("color 07");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t   *****GAME OVER*****\n\a");
    printf("\t\t\t\t   *****YOU DIED!***** \n");
    printf("\t\t\t\t*****YOUR SCORE:%4d*****\n\n", score / 20);
    printf("\t\t\t press y to continue，n to close(y/n)?\n");
    printf("\t\t\t");
end:;
    switch (getch()) {
        case 'y':
        case 'Y':
            death = 0, score = 0, memset(scr, 0, sizeof(scr)), run();
            break;
        case 'n':
        case 'N':
            break;
        default:
            goto end;
            break;
    }
}

void generate_block(
    int a[][N],
    int lala =
        rand() % 6 +
        1) {  //生成障碍，有三种依次为:从上至下的墙，飞弹，从下至上随机高度的墙。。。
    if (lala == 5) {
        for (int i = 0; i <= 19; i++) {
            a[i][69] = 2;
        }
    } else if (lala == 6) {
        int hehe = rand() % 5 + 1;
        if (hehe <= 1) {
            a[19][69] = 3;
        } else if (hehe <= 4) {
            a[14][69] = 3;
        } else if (hehe == 5) {
            a[21][69] = 3;
        }
    } else {
        for (int i = 0; i <= lala; i++)
            a[21 - i][69] = 2;
    }
}

void run() {  //主函数
    // system("color 70");
    shit = 0;
    day = 0;
    system("cls");
    srand(time(0));
    while (1) {
        score++;
        game_time++;
        if (game_time % 60 == 0)  //墙
            generate_block(scr);
        if (game_time % 80 == 0)  //飞弹
            generate_block(scr, 6);
        // if(game_time/1000>=1 && day==0)
        // system("color 07"),game_time=0,day=1;
        // //去掉这些注释（run函数里的所有）可开启昼夜更替（但我觉得不好看）。。。
        // else if(game_time/1000>=1 && day==1)
        // system("color 70"),game_time=0,day=0;
        days(day, scr);
        if (kbhit())  //读取输入
            switch (getch()) {
                case down:
                case 's':
                case 'S':
                    if (jump_time <= 15)
                        shift_time = 20, jump_time = 0;
                    break;
                case up:
                case 'W':
                case 'w':
                    if (jump_time <= 0)
                        jump_time = 25, jump_height = -1, shift_time = 0;
                    break;
                case 13:
                    system("pause");
                    break;
            }
        if (jump_time <= 0 && shift_time <= 0) {  //正常
            if (search_player(scr, 19, pl))
                drawplayer(scr, 19, pl);
            else
                goto end;            //新科技goto...感觉比break好用...
        } else if (jump_time > 0) {  //跳
            jump_time--;
            if (jump_time < 10) {
                jump_height--;
            } else if (jump_time > 15) {
                jump_height++;
            }
            if (search_player(scr, 19 - jump_height, pl)) {
                drawplayer(scr, 19 - jump_height, pl);
            } else
                goto end;
        } else if (shift_time > 0) {  //蹲
            shift_time--;
            if (search_player(scr, 20, pl))
                drawplayer(scr, 20, pl);
            else
                goto end;
        }
        for (int i = 4; i < 22; i++)  //移墙
            for (int j = 0; j <= 80; j++) {
                if (scr[i][j] == 2) {
                    scr[i][j] = 0;
                    if (j - 1 >= 0)
                        scr[i][j - 1] = 2;
                }
            }
        for (int i = 4; i < 22; i++)  //移飞弹，可见速度较墙快了一倍
            for (int j = 0; j <= 80; j++) {
                if (scr[i][j] == 3) {
                    scr[i][j] = 0;
                    if (scr[i][j - 1] == 1)
                        goto end;
                    else if (scr[i][j - 2] == 1)
                        goto end;
                    else if (j - 2 >= 0)
                        scr[i][j - 2] = 3;
                }
            }
        print(scr);
        for (int i = 4; i < 22; i++)
            for (int j = 0; j <= 80; j++) {
                if (scr[i][j] == 1)
                    scr[i][j] = 0;
            }
    }
end:;
    yn();
}

void menu() {
    system("color 07");
    ShowCursor(false);  //这一节照抄，指消去光标
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = false;
    SetConsoleCursorInfo(hOut, &cci);  //一直到这里照抄
}