#include <stdio.h>
int max(int a, int b) {
    if (a >= b)
        return a;
    return b;
}
int main() {
    int dp[32][3002] = {0};
    int x, n, a[32] = {0};
    scanf("%d%d", &n, &x);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int w = sum - x;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= w; j++) {
            if (j < a[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - a[i]] + a[i]);
        }
    }
    printf("%d", sum - dp[n][w]);
    return 0;
}