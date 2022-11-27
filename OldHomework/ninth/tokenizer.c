#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* ans;
int cnt = 0;  // number of ans's words
bool process(char* s, int len) {
    if (len == 0)
        return true;
    if (*(s + len - 1) == ';') {
        *(s + len - 1) = '\0';
        len--;
    }
    if (*s < '0' || *s > '9') {  //非数字开头
        if (!strcmp(s, "const") || !strcmp(s, "int") || !strcmp(s, "float") ||
            !strcmp(s, "double") || !strcmp(s, "long") ||
            !strcmp(s, "static") || !strcmp(s, "void") || !strcmp(s, "char") ||
            !strcmp(s, "extern") || !strcmp(s, "return") ||
            !strcmp(s, "break") || !strcmp(s, "enum") || !strcmp(s, "struct") ||
            !strcmp(s, "typedef") || !strcmp(s, "union") ||
            !strcmp(s, "goto")) {
            strcpy(ans + cnt * 9, "reserved");
            cnt++;
        } else if (!strcmp(s, "+") || !strcmp(s, "-") || !strcmp(s, "*") ||
                   !strcmp(s, "/") || !strcmp(s, "=") || !strcmp(s, "==") ||
                   !strcmp(s, "!=") || !strcmp(s, ">=") || !strcmp(s, "<=") ||
                   !strcmp(s, ">") || !strcmp(s, "<")) {
            strcpy(ans + cnt * 9, "operator");
            cnt++;
        } else if (*s == '.') {
            for (int i = 1; i < len; i++) {
                if (*(s + i) < '0' || *(s + i) > '9')
                    return false;
            }
            strcpy(ans + cnt * 9, "float");
            cnt++;
        } else {
            for (int i = 0; i < len; i++) {
                if (!((*(s + i) >= '0' && *(s + i) <= '9') ||
                      (*(s + i) >= 'a' && *(s + i) <= 'z') ||
                      (*(s + i) >= 'A' && *(s + i) <= 'Z') || *(s + i) == '_'))
                    return false;
            }
            strcpy(ans + cnt * 9, "variable");
            cnt++;
        }
    } else {  //数字开头
        bool flag = false;
        for (int i = 1; i < len; i++) {
            if (!(*(s + i) >= '0' && *(s + i) <= '9')) {
                if (*(s + i) == '.' && !flag) {
                    flag = true;
                } else {
                    return false;
                }
            }
        }
        if (flag) {
            strcpy(ans + cnt * 9, "float");
            cnt++;
        } else {
            strcpy(ans + cnt * 9, "integer");
            cnt++;
        }
    }
    return true;
}
int main() {
    ans = (char*)malloc(3000 * 9);
    char* s;
    s = (char*)malloc(4096);
    bool flag = true;
    while (scanf("%s", s) != EOF) {
        char* p = strchr(s, ';');
        if (p == NULL)
            flag = flag && process(s, strlen(s));
        else {
            *p = '\0';
            flag = flag && process(s, strlen(s) - strlen(p));
            *(ans + cnt * 9) = '\n';
            cnt++;
            flag = flag && process(p + 1, strlen(p + 1));
        }
    }
    if (flag) {
        for (int i = 0; i < cnt; i++) {
            if (*(ans + i * 9) != '\n')
                printf("%s ", ans + i * 9);
            else if (i != cnt - 1)
                putchar('\n');
        }
    } else {
        printf("Compile Error");
    }
    return 0;
}