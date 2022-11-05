#include <stdio.h>
#define SIZE 10000
int n, a[SIZE];

int Over() {  //结束为真
    int flag = 1, sum = 0;
    for (int x = 0; x < n; x++) {
        sum = sum + a[x];
        if (sum >= 2) {
            flag = 0;
            break;
        }
    }
    return flag;
}
int main() {
    int k, cnt = 0, ans = 0;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        a[i] = 1;
    }
    while (!Over()) {
        for (int i = 0; i < n; i++) {
            if (a[i]) {
                cnt++;
                if (cnt == k) {
                    a[i] = 0;
                    cnt = 0;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i]) {
            ans = i + 1;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
