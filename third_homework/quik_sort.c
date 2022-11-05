#include <stdio.h>
#define SIZE 100000
int main() {
    int n, k, a[SIZE];
    scanf("%d %d", &n, &k);
    int l, r;
    k = k - 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    l = 0;
    r = n - 1;
    while (l != r) {
        for (; a[l] < a[k] && l != r; l++)
            ;
        for (; a[r] >= a[k] && l != r; r--)
            ;
        if (l != r) {
            a[l] = a[l] + a[r];
            a[r] = a[l] - a[r];
            a[l] = a[l] - a[r];
            if (l == k) {
                k = r;
            } else if (r == k) {
                k = l;
            }
        }
    }
    if (a[l] > a[k] && l < k) {
        a[l] = a[l] + a[k];
        a[k] = a[l] - a[k];
        a[l] = a[l] - a[k];
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}