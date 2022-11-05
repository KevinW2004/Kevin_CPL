#include <stdio.h>
#define SIZE 10000
char s[SIZE];
int N, len;

int transform(char a) {
    int x;
    if (a >= '0' && a <= '9') {
        x = a - '0';
    } else {
        x = a - 'A' + 10;
    }
    return x;
}

int isValid() {
    int flag = 1;
    for (int i = 0; i < len; i++) {
        if (transform(s[i]) >= N) {
            flag = 0;
            break;
        }
    }
    return flag;
}
int main() {
    int ans = 0;
    scanf("%d %d", &len, &N);
    scanf("%s", s);
    if (!isValid()) {
        printf("Error\n");
    } else {
        for (int i = 0; i < len; i++) {
            ans = ans * N + transform(s[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}