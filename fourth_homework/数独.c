#include <stdio.h>
void initialize(int* a) {
    for (int i = 0; i < 9; i++) {
        a[i] = 0;
    }
    return;
}
int main() {
    int a[9][9] = {0};
    int ans = 1;  // 1 is Yes
    int flag[9] = {0};
    initialize(flag);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] < 1 || a[i][j] > 9)
                ans = 0;
        }
    }

    if (ans) {
        for (int i = 0; i < 9; i++) {  //检查每一行
            initialize(flag);
            for (int j = 0; j < 9; j++) {
                if (flag[a[i][j] - 1])
                    ans = 0;
                else
                    flag[a[i][j] - 1] = 1;
            }
        }
        for (int i = 0; i < 9; i++) {  //检查每一列
            initialize(flag);
            for (int j = 0; j < 9; j++) {
                if (flag[a[j][i] - 1])
                    ans = 0;
                else
                    flag[a[j][i] - 1] = 1;
            }
        }
        for (int i = 0; i < 3; i++) {  //检查每一九宫格
            for (int j = 0; j < 3; j++) {
                initialize(flag);
                for (int row = i * 3; row < i * 3 + 3; row++) {
                    for (int col = j * 3; col < j * 3 + 3; col++) {
                        if (flag[a[row][col] - 1])
                            ans = 0;
                        else
                            flag[a[row][col] - 1] = 1;
                    }
                }
            }
        }
    }

    if (ans)
        printf("YES");
    else
        printf("NO");

    return 0;
}