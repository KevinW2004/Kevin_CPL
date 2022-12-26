#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
/* int main() {
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7, x8 = 8, x9 = 9,
        x10 = 10;
    printf("%d", x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8 + x9 + x10);
    return 0;
}
// 组合数
int Choose(int a, int b) {
    if (b == 0 || b == a)
        return 1;
    return Choose(a - 1, b - 1) + Choose(a - 1, b);
}
void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} */

#include "API\API.h"
Node* head = NULL;
int main() {
    int val[3];
    scanf("%d%d%d", &val[0], &val[1], &val[2]);
    Append(head, val[2]);
    Append(head, val[1]);
    Append(head, val[0]);
    PrintList(head);
    return 0;
}