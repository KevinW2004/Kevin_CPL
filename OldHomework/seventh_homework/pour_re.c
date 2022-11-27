#include <stdbool.h>
#include <stdio.h>
const short a = 0, b = 1, c = 2;
int max[3], aim[3];
int k;
short Judge(int cur[]) {
    for (int i = 0; i < 3; i++) {
        if (cur[i] != aim[i])
            return 0;
    }
    return 1;
}
void Pour(int from, int to, int pre[], int nex[]) {
    nex[to] = pre[to] + pre[from];
    if (nex[to] > max[to])
        nex[to] = max[to];
    nex[from] = 0;
    nex[3 - from - to] = pre[3 - from - to];
}
bool growTree(int cur[], int step) {
    if (step > k)
        return 0;
    bool flag = false;
    int tmp[6][3];
    Pour(a, b, cur, tmp[0]);
    Pour(a, c, cur, tmp[1]);
    Pour(b, c, cur, tmp[2]);
    Pour(b, a, cur, tmp[3]);
    Pour(c, a, cur, tmp[4]);
    Pour(c, b, cur, tmp[5]);
    for (int i = 0; i < 6; i++) {
        if (Judge(tmp[i]))
            return true;
    }
    for (int i = 0; i < 6 && !flag; i++) {
        flag = flag || growTree(tmp[i], step + 1);
    }
    return flag;
}
int main() {
    int cur[3];
    scanf("%d%d%d%d%d%d%d%d%d%d", &k, &max[a], &max[b], &max[c], &cur[a],
          &cur[b], &cur[c], &aim[a], &aim[b], &aim[c]);
    if (k) {
        printf(growTree(cur, 1) ? "Yes" : "No");
    } else {
        printf(Judge(cur) ? "Yes" : "No");
    }
    return 0;
}
//以下为改进思路
/**bool solved = false;
void pour(int step, int a, int b, int c) {
    if (step > k)
        return;
    if (true) {
        solved = true;
        return;
    }
    if (solved)
        return;
    pour(step + 1, 0, min((a + b), vb), c)
}*/