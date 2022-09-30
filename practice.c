#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const double PI = 3.1415;
int main()
{
    int radius = 10;
    printf("周长=%10.4f\n面积=%10.4f", 2 * PI * radius, PI * pow(radius, 2));

    return 0;
}
