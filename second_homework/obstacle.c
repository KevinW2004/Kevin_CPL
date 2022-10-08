#include <math.h>
#include <stdio.h>

const int A = 0, B = 1, C = 2;
int x[3], y[3], Cur_x, Cur_y;
char ans[1000005] = {""};
int step = 0;
void moveX() {
    if (Cur_x < x[B]) {
        Cur_x++;
        ans[step] = 'R';
        step++;
    } else if (Cur_x > x[B]) {
        Cur_x--;
        ans[step] = 'L';
        step++;
    }
}
void moveY() {
    if (Cur_y < y[B]) {
        Cur_y++;
        ans[step] = 'U';
        step++;
    } else if (Cur_y > y[B]) {
        Cur_y--;
        ans[step] = 'D';
        step++;
    }
}
int main() {
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    Cur_x = x[A];
    Cur_y = y[A];

    while (Cur_y != y[B] || Cur_x != x[B]) {
        if (Cur_x != x[B] && !(fabs(Cur_x - x[C]) == 1 && Cur_y == y[C]) &&
            !(fabs(Cur_x - x[C]) == 1 && x[C] == x[B])) {
            moveX();
        } else if (Cur_y != y[B]) {
            moveY();
        } else {
            moveX();
        }
    }
    printf("%d\n%s\n", step, ans);
    return 0;
}
