#include <stdio.h>
const short a = 0, b = 1, c = 2;
int max[3], aim[3];
int cur[13000000][3] = {0};  // cur是一棵六叉树 使用temp时改为13000000
int temp[3] = {0};           // 为了省内存而取代最后一层
//  1 means OK
short Judge(int state) {
    for (int i = 0; i < 3; i++) {
        if (cur[state][i] != aim[i])
            return 0;
    }
    return 1;
}
short Pour(int from, int to, int state1, int state2) {
    cur[state2][to] = cur[state1][to] + cur[state1][from];
    if (cur[state2][to] > max[to])
        cur[state2][to] = max[to];
    cur[state2][from] = 0;
    cur[state2][3 - from - to] = cur[state1][3 - from - to];
    return Judge(state2);
}
short tempPour(int from, int to, int state1) {
    temp[to] = cur[state1][to] + cur[state1][from];
    if (temp[to] > max[to])
        temp[to] = max[to];
    temp[from] = 0;
    temp[3 - from - to] = cur[state1][3 - from - to];
    for (int i = 0; i < 3; i++) {
        if (temp[i] != aim[i])
            return 0;
    }
    return 1;
}
short growTree(int state) {
    short flag = 0;
    flag += Pour(a, b, state, 6 * state + 1);
    flag += Pour(a, c, state, 6 * state + 2);
    flag += Pour(b, c, state, 6 * state + 3);
    flag += Pour(b, a, state, 6 * state + 4);
    flag += Pour(c, a, state, 6 * state + 5);
    flag += Pour(c, b, state, 6 * state + 6);
    return flag ? 1 : 0;
}
int main() {
    int k;
    scanf("%d%d%d%d%d%d%d%d%d%d", &k, &max[a], &max[b], &max[c], &cur[0][a],
          &cur[0][b], &cur[0][c], &aim[a], &aim[b], &aim[c]);
    int state, state0 = 0;
    short flag = 0;
    for (short step = 1; step < k && !flag; step++, state0 = state0 * 6 + 1) {
        for (state = state0; state <= state0 * 6; state++) {
            flag += growTree(state);
        }
    }

    for (state = state0; state <= state0 * 6 && !flag; state++) {
        flag += tempPour(a, b, state);
        flag += tempPour(a, c, state);
        flag += tempPour(b, c, state);
        flag += tempPour(b, a, state);
        flag += tempPour(c, a, state);
        flag += tempPour(c, b, state);
    }

    printf(flag ? "Yes" : "No");
    return 0;
}