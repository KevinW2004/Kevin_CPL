#include <math.h>
#include <stdio.h>
#define M 19260817
int factors[100000];  // all prime factors
int n = 0;            // Number of factors
bool isPrime(int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
bool isOverlapped(int x) {
    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (factors[i] == x) {
            flag = true;
            break;
        }
    }
    return flag;
}
void FindFactor(int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0 && isPrime(i) && !isOverlapped(i)) {
            factors[n++] = i;
        }
    }
}
int main() {
    int x, y, ans;
    scanf("%d %d", &x, &y);
    FindFactor(x);
    FindFactor(y);
}