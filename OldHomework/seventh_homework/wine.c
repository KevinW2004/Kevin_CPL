#include <stdio.h>
#define SIZE 10005
int Index[SIZE] = {0};
void swap(int i, int j) {
    int temp = Index[i];
    Index[i] = Index[j];
    Index[j] = temp;
}
int main() {
    int n, L, v[SIZE], w[SIZE];
    int value = 0, weight = 0;
    scanf("%d%d", &n, &L);
    for (int i = 0; i < n; i++) {
        Index[i] = i;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        for (int t = i; v[Index[t]] > v[Index[t - 1]] && t >= 1; t--) {
            swap(t, t - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    int t = 0;
    for (; t < n && weight < L; t++) {
        weight += w[Index[t]];
        value += v[Index[t]] * w[Index[t]];
    }
    if (weight > L) {
        t--;
        weight -= w[Index[t]];
        value -= v[Index[t]] * w[Index[t]];
        value += v[Index[t]] * (L - weight);
    }
    printf("%d\n", value);
    return 0;
}