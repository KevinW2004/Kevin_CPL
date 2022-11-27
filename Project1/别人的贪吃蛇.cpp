// https://gitee.com/devcpp/cgames    anbangli@foxmail.com    GNU GPL v3
// cgame7(snake)v2    贪吃蛇第2版：使用结构体顺序表实现贪吃蛇功能

#include <conio.h>
#include <windows.h>
#include <ctime>
#include <iostream>
using namespace std;

const short int WD = 30, HT = 20;  //游戏地图的宽度(Width)和高度(Height)
short int map[HT][WD] = {0};  //游戏地图为 HT 行 WD 列，并全部初始化为0（空白）
//注意：上墙和下墙的行号为 0 和 HT-1，左墙和右墙的列号为 0 和 WD-1，
//中心区域的行号为[1, HT-2]，列号为[1, WD-2]。程序中要注意正确使用这些行列号。
short int sx, sy, len;  //蛇头坐标(sx, sy)，蛇长len
short int x[(WD - 2) * (HT - 2)],
    y[(WD - 2) * (HT - 2)];  //表示蛇体格点的坐标x值和y值
//上面两个数组中的存储内容：蛇尾-蛇体-蛇体-...-蛇体-蛇颈-蛇头
short int foodx, foody;  //食物坐标(foodx, foody)

void gotoxy(short x, short y) {  //控制台窗口光标定位
    static COORD crd;  //定义 COORD 类型(窗口坐标)的静态局部变量 crd
    crd.X = x;
    crd.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
    return;
}
/* void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);  //两个参数分别是指定哪个窗体，具体位置
} */
void showcursor(bool visible) {  //显示或隐藏光标
    CONSOLE_CURSOR_INFO cursor = {20, visible};
    //用参数visible指定光标是否可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    //设定光标 	return;
}

void initGame() {  //初始化游戏
    //初始化地图
    for (int i = 0, j = 0; i < HT; i++)
        for (j = 0; j < WD; j++)
            if (i == 0 || i == HT - 1 || j == 0 || j == WD - 1)
                map[i][j] = -2;  //围墙（-2）
    //初始化蛇体
    sx = WD / 3;
    sy = HT / 2;
    len = 4;
    for (int i = 0; i <= len; i++) {
        x[i] = sx;
        y[i] = sy;
        map[sx][sy] = 1;  //蛇体格点表示为1
    }

    srand(time(0));  //初始化随机数种子
    //初始化食物（-1）
    foodx = rand() % (WD - 2) + 1;
    foody = rand() % (HT - 2) + 1;
    map[foody][foodx] = -1;  //食物
}

void drawMap() {  //绘制游戏地图框架
    gotoxy(WD / 2, 0);
    cout << "  S n a k e   g a m e" << endl;  //顶行显示游戏名称
    for (int i = 0, j = 0; i < HT; i++)  //绘制地图框架（仅包含围墙和空白）
        for (j = 0; j < WD; j++) {
            gotoxy(j * 2, i + 1);
            cout << (map[i][j] == -2 ? "█" : "  ");
        }
}

void drawSnake() {  //绘制蛇体
    gotoxy(x[0] * 2, y[0] + 1);
    cout << "  ";  //擦除上一步的蛇尾
    gotoxy(x[len - 1] * 2, y[len - 1] + 1);
    cout << "◎";  //蛇颈
    gotoxy(x[len] * 2, y[len] + 1);
    cout << "＠";  //蛇头
}

void drawFoodLen() {  //绘制食物和蛇长信息
    gotoxy(foodx * 2, foody + 1);
    cout << "☆";  //绘制食物
    gotoxy(0, HT + 1);
    cout << "length: " << len;  //显示蛇体长度
}

void gameOver(const char msg[]) {  //游戏结束，输出信息
    gotoxy(0, HT + 2);
    cout << msg;
}

bool wantExit() {  //询问是否结束游戏
    showcursor(true);
    gotoxy(0, HT + 2);
    cout << "结束游戏 (y/n)?";
    int key;
    if ((key = getch()) == 'y' || key == 'Y')
        return true;
    showcursor(false);
    gotoxy(0, HT + 2);
    cout << "                 ";  //擦除此行文字
    return false;
}

int main() {
    const short int ESC = 27, LEFT = 75, UP = 72, RIGHT = 77,
                    DOWN = 80;  //键值常量
    short int move = RIGHT,
              key = RIGHT;  // move表示蛇当前运动方向，key表示用户按键值

    initGame();         //初始化游戏
    showcursor(false);  //隐藏光标
    drawMap();          //绘制游戏地图框架
    drawFoodLen();      //首次绘制食物并输出蛇长

    while (true) {  //主循环。循环条件为 true，循环中使用 break 中止循环
        drawSnake();        //绘制蛇体
        Sleep(200);         //延时
        if (kbhit()) {      //检测用户是否按键
            key = getch();  //获取用户按键值
            if (key <= 0 || key > 127)  //读取方向键时，第一次读得的不是实际键值
                key = getch();  //读取方向键时，第二次才读得实际键值
            if (key == ESC && wantExit()) {  // ESC键结束游戏
                gameOver("谢谢使用！再见！");
                break;  //跳出游戏主循环
            }
            if ((key == LEFT && move != RIGHT) ||
                (key == RIGHT && move != LEFT) || (key == UP && move != DOWN) ||
                (key == DOWN && move != UP))
                move = key;
        }
        if ((move == LEFT && --sx <= 0) || (move == RIGHT && ++sx == WD - 1) ||
            (move == UP && --sy <= 0) || (move == DOWN && ++sy == HT - 1)) {
            gameOver("蛇头撞墙，游戏结束。");
            break;  //跳出游戏主循环
        }
        if (map[sy][sx] > 0) {  //撞到自身
            gameOver("蛇头撞到自身，游戏结束。");
            break;                       //跳出游戏主循环
        } else if (map[sy][sx] != -1) {  //正常移动：蛇头和蛇身都要变
            map[y[0]][x[0]] = 0;
            for (int i = 0; i < len; i++) {  //蛇身和蛇颈各个格点前移
                x[i] = x[i + 1];
                y[i] = y[i + 1];
            }
        } else if (map[sy][sx] == -1) {  //吃到食物
            len++;                       //蛇体长度增1，蛇身不变
            do {                         //在空白场地产生新食物
                foodx = rand() % (WD - 2) + 1;
                foody = rand() % (HT - 2) + 1;
            } while (map[foody][foodx] != 0);
            map[foody][foodx] = -1;  //地图中食物位置赋值为-1
            drawFoodLen();           //绘制食物和蛇长信息
        }
        //正常移动或吃到食物，蛇头都要变
        x[len] = sx;      //蛇头坐标x
        y[len] = sy;      //蛇头坐标y
        map[sy][sx] = 1;  //地图中蛇头位置赋值为1
    }
    showcursor(true);
    getchar();
    return 0;
}
