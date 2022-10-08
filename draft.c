#include <math.h>
#include <stdio.h>
int main() {
    printf("%lf\n",
           5 * pow(16, 3) + 4 * pow(16, 2) + 2 * pow(16, 1) + 2 * pow(16, 0));
    return 0;
}