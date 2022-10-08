#include <math.h>
#include <stdio.h>

const int A = 0, B = 1, C = 2;
int x[3], y[3], Cur_x, Cur_y;
char ans[2000005] = {""};
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
        } else if ((x[B] - x[C]) * (x[C] - Cur_x) > 0 && y[B] == y[C] &&
                   fabs(x[C] - Cur_x) == 1) {
            Cur_y++;
            ans[step] = 'U';
            step++;
        } else if ((y[B] - y[C]) * (y[C] - Cur_y) > 0 && x[B] == x[C] &&
                   x[C] == Cur_x && fabs(y[C] - Cur_y) == 1) {
            Cur_x++;
            ans[step] = 'R';
            step++;
            moveY();
        } else if (Cur_y != y[B]) {
            moveY();
        } else {
            moveX();
        }
        if (Cur_x == x[C] && Cur_y == y[C])
            printf("error\n");
    }
    printf("%d\n%s\n", step, ans);
    return 0;
}
