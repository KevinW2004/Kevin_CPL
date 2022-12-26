// https://gitee.com/devcpp/cgames    anbangli@foxmail.com    GNU GPL v3
// cgame7(snake)v2    ̰���ߵ�2�棺ʹ�ýṹ��˳���ʵ��̰���߹���

#include <conio.h>
#include <windows.h>
#include <ctime>
#include <iostream>
using namespace std;

const short int WD = 30, HT = 20;  //��Ϸ��ͼ�Ŀ��(Width)�͸߶�(Height)
short int map[HT][WD] = {0};  //��Ϸ��ͼΪ HT �� WD �У���ȫ����ʼ��Ϊ0���հף�
//ע�⣺��ǽ����ǽ���к�Ϊ 0 �� HT-1����ǽ����ǽ���к�Ϊ 0 �� WD-1��
//����������к�Ϊ[1, HT-2]���к�Ϊ[1, WD-2]��������Ҫע����ȷʹ����Щ���кš�
short int sx, sy, len;  //��ͷ����(sx, sy)���߳�len
short int x[(WD - 2) * (HT - 2)],
    y[(WD - 2) * (HT - 2)];  //��ʾ�����������xֵ��yֵ
//�������������еĴ洢���ݣ���β-����-����-...-����-�߾�-��ͷ
short int foodx, foody;  //ʳ������(foodx, foody)

void gotoxy(short x, short y) {  //����̨���ڹ�궨λ
    static COORD crd;  //���� COORD ����(��������)�ľ�̬�ֲ����� crd
    crd.X = x;
    crd.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
    return;
}
/* void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  // ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);  //���������ֱ���ָ���ĸ����壬����λ��
} */
void showcursor(bool visible) {  //��ʾ�����ع��
    CONSOLE_CURSOR_INFO cursor = {20, visible};
    //�ò���visibleָ������Ƿ�ɼ�
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    //�趨��� 	return;
}

void initGame() {  //��ʼ����Ϸ
    //��ʼ����ͼ
    for (int i = 0, j = 0; i < HT; i++)
        for (j = 0; j < WD; j++)
            if (i == 0 || i == HT - 1 || j == 0 || j == WD - 1)
                map[i][j] = -2;  //Χǽ��-2��
    //��ʼ������
    sx = WD / 3;
    sy = HT / 2;
    len = 4;
    for (int i = 0; i <= len; i++) {
        x[i] = sx;
        y[i] = sy;
        map[sx][sy] = 1;  //�������ʾΪ1
    }

    srand(time(0));  //��ʼ�����������
    //��ʼ��ʳ�-1��
    foodx = rand() % (WD - 2) + 1;
    foody = rand() % (HT - 2) + 1;
    map[foody][foodx] = -1;  //ʳ��
}

void drawMap() {  //������Ϸ��ͼ���
    gotoxy(WD / 2, 0);
    cout << "  S n a k e   g a m e" << endl;  //������ʾ��Ϸ����
    for (int i = 0, j = 0; i < HT; i++)  //���Ƶ�ͼ��ܣ�������Χǽ�Ϳհף�
        for (j = 0; j < WD; j++) {
            gotoxy(j * 2, i + 1);
            cout << (map[i][j] == -2 ? "��" : "  ");
        }
}

void drawSnake() {  //��������
    gotoxy(x[0] * 2, y[0] + 1);
    cout << "  ";  //������һ������β
    gotoxy(x[len - 1] * 2, y[len - 1] + 1);
    cout << "��";  //�߾�
    gotoxy(x[len] * 2, y[len] + 1);
    cout << "��";  //��ͷ
}

void drawFoodLen() {  //����ʳ����߳���Ϣ
    gotoxy(foodx * 2, foody + 1);
    cout << "��";  //����ʳ��
    gotoxy(0, HT + 1);
    cout << "length: " << len;  //��ʾ���峤��
}

void gameOver(const char msg[]) {  //��Ϸ�����������Ϣ
    gotoxy(0, HT + 2);
    cout << msg;
}

bool wantExit() {  //ѯ���Ƿ������Ϸ
    showcursor(true);
    gotoxy(0, HT + 2);
    cout << "������Ϸ (y/n)?";
    int key;
    if ((key = getch()) == 'y' || key == 'Y')
        return true;
    showcursor(false);
    gotoxy(0, HT + 2);
    cout << "                 ";  //������������
    return false;
}

int main() {
    const short int ESC = 27, LEFT = 75, UP = 72, RIGHT = 77,
                    DOWN = 80;  //��ֵ����
    short int move = RIGHT,
              key = RIGHT;  // move��ʾ�ߵ�ǰ�˶�����key��ʾ�û�����ֵ
    system("cls");
    initGame();         //��ʼ����Ϸ
    showcursor(false);  //���ع��
    drawMap();          //������Ϸ��ͼ���
    drawFoodLen();      //�״λ���ʳ�ﲢ����߳�

    while (true) {  //��ѭ����ѭ������Ϊ true��ѭ����ʹ�� break ��ֹѭ��
        drawSnake();        //��������
        Sleep(200);         //��ʱ
        if (kbhit()) {      //����û��Ƿ񰴼�
            key = getch();  //��ȡ�û�����ֵ
            if (key <= 0 || key > 127)  //��ȡ�����ʱ����һ�ζ��õĲ���ʵ�ʼ�ֵ
                key = getch();  //��ȡ�����ʱ���ڶ��βŶ���ʵ�ʼ�ֵ
            if (key == ESC && wantExit()) {  // ESC��������Ϸ
                gameOver("ллʹ�ã��ټ���");
                break;  //������Ϸ��ѭ��
            }
            if ((key == LEFT && move != RIGHT) ||
                (key == RIGHT && move != LEFT) || (key == UP && move != DOWN) ||
                (key == DOWN && move != UP))
                move = key;
        }
        if ((move == LEFT && --sx <= 0) || (move == RIGHT && ++sx == WD - 1) ||
            (move == UP && --sy <= 0) || (move == DOWN && ++sy == HT - 1)) {
            gameOver("��ͷײǽ����Ϸ������");
            break;  //������Ϸ��ѭ��
        }
        if (map[sy][sx] > 0) {  //ײ������
            gameOver("��ͷײ��������Ϸ������");
            break;                       //������Ϸ��ѭ��
        } else if (map[sy][sx] != -1) {  //�����ƶ�����ͷ������Ҫ��
            map[y[0]][x[0]] = 0;
            for (int i = 0; i < len; i++) {  //������߾��������ǰ��
                x[i] = x[i + 1];
                y[i] = y[i + 1];
            }
        } else if (map[sy][sx] == -1) {  //�Ե�ʳ��
            len++;                       //���峤����1��������
            do {                         //�ڿհ׳��ز�����ʳ��
                foodx = rand() % (WD - 2) + 1;
                foody = rand() % (HT - 2) + 1;
            } while (map[foody][foodx] != 0);
            map[foody][foodx] = -1;  //��ͼ��ʳ��λ�ø�ֵΪ-1
            drawFoodLen();           //����ʳ����߳���Ϣ
        }
        //�����ƶ���Ե�ʳ���ͷ��Ҫ��
        x[len] = sx;      //��ͷ����x
        y[len] = sy;      //��ͷ����y
        map[sy][sx] = 1;  //��ͼ����ͷλ�ø�ֵΪ1
    }
    showcursor(true);
    getchar();
    return 0;
}
