#include <math.h>
#include <stdio.h>
/*int JC(int x) {
    int ans = 1;
    if (x != 0) {
        for (int i = x; i >= 2; i--) {
            ans *= i;
        }
    }
    return ans;
}
int Choose(int n, int m) {
    int ans;
    ans = JC(n) / (JC(m) * JC(n - m));
    return ans;
}
*/
int main() {
    int n, ans;
    scanf("%d", &n);
    switch (n) {
        case 1:
            ans = 0;
            break;
        case 2:
            ans = 2;
            break;
        case 3:
            ans = 4;
            break;

        default:
            ans =
                (n * (n - 1) * (n - 2) * (n - 3)) / 24 + (n * (n - 1)) / 2 + 1;
            break;
    }
    printf("%d\n", ans);
    return 0;
}
/*int main() {
    int n, ans;
    scanf("%d", &n);
    ans = ((1.0 / 24) * pow(n, 4)) - (1.0 / 4) * pow(n, 3) +
          (23.0 / 24) * pow(n, 2) - (3.0 / 4) * n + 1;
    printf("%d\n", ans);
    return 0;
}
*/