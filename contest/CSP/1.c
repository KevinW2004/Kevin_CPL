#include <stdio.h>
int a[21] = {0}, b[21] = {0}, c[21] = {0};
int main() {
    int m, n;
    c[0] = 1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        c[i] = c[i - 1] * a[i];
        b[i] = ((m % c[i]) - (m % c[i - 1])) / c[i - 1];
        printf("%d ", b[i]);
    }
    return 0;
}