#include <math.h>
#include <stdio.h>

double powPro(double a, double b) {
    double ans;
    if (a == 0)
        ans = 0;
    else
        ans = pow(fabs(a), b) * (fabs(a) / a);
    return ans;
}

int main() {
    int p, q;
    double p_, q_, x;
    scanf("%d %d", &p, &q);
    p_ = (double)p / 3.0;
    q_ = (double)q / 2.0;
    x = powPro(-q_ + sqrt(pow(q_, 2) + powPro(p_, 3)), 1.0 / 3) +
        powPro(-q_ - sqrt(pow(q_, 2) + powPro(p_, 3)), 1.0 / 3);
    printf("%.3f", x);
    return 0;
}
