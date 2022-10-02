#include <math.h>
#include <stdio.h>

int main() {
    const double G = 6.67e-11;
    const double M = 77.15;
    double m, R, F;

    scanf("%lf %lf", &m, &R);
    F = (G * M * m) / pow(R, 2);
    printf("%.3e\n", F);
    return 0;
}