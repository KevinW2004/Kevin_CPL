#include <stdio.h>
#include <string.h>
int a, b, c;
int x[2] = {0}, y[2] = {0};
void rotate(char act);
void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
int main() {
    char act[1005];
    scanf("%d%d%d", &a, &b, &c);
    x[1] = a;
    y[1] = b;
    scanf("%s", act);
    for (int i = 0; i < strlen(act); i++) {
        rotate(act[i]);
    }
    printf("%d %d %d %d\n", x[0], x[1], y[0], y[1]);
    return 0;
}
void rotate(char act) {
    switch (act) {
        case 'W':
            swap(&x[0], &x[1]);
            x[0] = x[1] - c;
            swap(&a, &c);
            break;
        case 'A':
            swap(&y[0], &y[1]);
            y[0] = y[1] - c;
            swap(&b, &c);
            break;
        case 'S':
            swap(&x[0], &x[1]);
            x[1] = x[0] + c;
            swap(&a, &c);
            break;
        case 'D':
            swap(&y[0], &y[1]);
            y[1] = y[0] + c;
            swap(&b, &c);
            break;
    }
}