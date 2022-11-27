#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Width 1000
typedef struct Arg {
    char name;
    bool type;  // 1 = need data
} arg;
arg* dic = NULL;
int cnt = 0;           // number of the dictionary
short error_type = 0;  // 0 is ok;1 is invalid option;2 is lacking argument
char error = 0;
char* ans;
int ans_cnt = 0;
int findNO(char a) {
    for (int i = 0; i < cnt; i++) {
        if ((dic + i)->name == a) {
            return i;
        }
    }
    return -1;
}
void BUildDic(char* rule, int lenR) {
    dic = (arg*)malloc(lenR * sizeof(arg));
    for (int i = 0; i < lenR;) {
        (dic + cnt)->name = *(rule + i);
        (dic + cnt)->type = 0;
        if (*(rule + i + 1) == ':') {
            (dic + cnt)->type = 1;
            i++;
        }
        i++;
        cnt++;
    }
}
void Print() {
    switch (error_type) {
        case 0:
            for (int i = 0; i < ans_cnt; i++) {
                printf("%s\n", ans + i * Width);
            }
            break;
        case 1:
            printf("%s: invalid option -- '%c'\n", ans, error);
            break;
        case 2:
            printf("%s: option requires an argument -- '%c'\n", ans, error);
            break;
    }
}
int main() {
    char *rule, *cmd;
    rule = (char*)malloc(200);
    cmd = (char*)malloc(2000);

    scanf("%s", rule);
    int lenR = strlen(rule);
    ans = (char*)malloc(lenR * Width);
    memset(ans, '\0', sizeof(ans));
    BUildDic(rule, lenR);

    scanf("%s", ans);
    getchar();
    ans_cnt++;
    bool flag = true;  // false 为正在输入参数
    while (scanf("%s", cmd) != EOF) {
        if (*cmd == '-' && flag) {
            int NO = findNO(*(cmd + 1));
            if (NO == -1) {
                error_type = 1;
                error = *(cmd + 1);
                break;
            } else {
                *(ans + ans_cnt * Width) = *(cmd + 1);
                *(ans + ans_cnt * Width + 1) = '\0';
                if ((dic + NO)->type) {
                    strcat((ans + ans_cnt * Width), "=\0");
                    flag = false;
                } else {
                    ans_cnt++;
                }
            }
        } else if (!flag) {
            strcat((ans + ans_cnt * Width), cmd);
            ans_cnt++;
            flag = true;
        }
    }
    if (!flag && !error_type) {
        error_type = 2;
        error = *(cmd + 1);
    }
    Print();
    free(ans);
    free(cmd);
    free(rule);
    free(dic);
    return 0;
}