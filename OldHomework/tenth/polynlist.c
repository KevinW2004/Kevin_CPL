#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char x[12] = {'\0'};
typedef struct Polynomial {
    int n;
    int* a;
} Poly;
Poly p[2];
Poly ans;
void PrintPoly(const Poly p) {
    for (int i = p.n; i >= 0; i--) {
        if (p.a[i] != 0) {
            if (i != p.n && p.a[i] > 0)
                putchar('+');
            if (i != 0) {
                if (p.a[i] == -1)
                    putchar('-');
                else if (p.a[i] != 1)
                    printf("%d", p.a[i]);
            }
            if (i != 1 && i != 0)
                printf("%s^%d", x, i);
            else if (i == 1)
                printf("%s", x);
            else if (i == 0)
                printf("%d", p.a[i]);
        }
    }
    putchar('\n');
}
void AddPoly() {
    short m = p[0].n > p[1].n ? 0 : 1;
    ans.n = p[m].n;
    for (int i = ans.n; i >= 0; i--) {
        if (i > p[1 - m].n)
            ans.a[i] = p[m].a[i];
        else
            ans.a[i] = p[0].a[i] + p[1].a[i];
    }
    PrintPoly(ans);
}
void MinusPoly() {
    short m = p[0].n > p[1].n ? 0 : 1;
    ans.n = p[m].n;
    for (int i = ans.n; i >= 0; i--) {
        if (i > p[1 - m].n)
            ans.a[i] = p[m].a[i] * (int)pow(-1, m);
        else
            ans.a[i] = p[0].a[i] - p[1].a[i];
    }
    PrintPoly(ans);
}
void MultiPoly() {
    ans.n = p[0].n + p[1].n;
    memset(ans.a, 0, (p[0].n + p[1].n + 1) * sizeof(int));
    for (int i = p[0].n; i >= 0; i--) {
        for (int j = p[1].n; j >= 0; j--) {
            ans.a[i + j] += p[0].a[i] * p[1].a[j];
        }
    }
    PrintPoly(ans);
}
int main() {
    scanf("%d%d", &p[0].n, &p[1].n);
    scanf("%s", x);
    ans.a = (int*)malloc((p[0].n + p[1].n + 1) * sizeof(int));
    for (int i = 0; i < 2; i++) {
        p[i].a = (int*)malloc((p[i].n + 1) * sizeof(int));
        for (int j = p[i].n; j >= 0; j--) {
            scanf("%d", &p[i].a[j]);
        }
    }
    AddPoly();
    MinusPoly();
    MultiPoly();
    return 0;
}