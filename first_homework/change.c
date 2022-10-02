#include <stdio.h>

int main() {
    int n, i;
    int bill[5] = {0};
    const int money[5] = {50, 20, 10, 5, 1};

    scanf("%d", &n);
    for (i = 0; i <= 4; i++) {
        bill[i] = n / money[i];
        n = n - bill[i] * money[i];
        if (n == 0)
            break;
    }
    for (i = 0; i <= 4; i++)
        printf("%d\n", bill[i]);
    return 0;
}
