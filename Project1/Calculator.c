#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
short Precedence(char a) {
    if (a == '+' || a == '-') {
        return 1;
    } else if (a == '*' || a == '/') {
        return 2;
    }
    return 0;
}
typedef struct Stack {
    int top;
    union {
        int d[1024];
        char m[1024];
    } data;
} stack;
typedef struct Ass {
    char name[32];
    union {
        int d;
    } val;
} ass;
stack *marks, *numbers;
ass assignments[128];
unsigned short a_cnt = 0;  // number of assignments
void Initialize() {
    marks = (stack*)malloc(sizeof(stack));
    numbers = (stack*)malloc(sizeof(stack));
    marks->top = 0;
    numbers->top = 0;
    memset(marks->data.m, 0, sizeof(marks->data.m));
    memset(numbers->data.d, 0, sizeof(numbers->data.d));
}
int popD(stack* s) {
    return s->data.d[--(s->top)];
}
char popM(stack* s) {
    return s->data.m[--(s->top)];
}
void pushD(stack* s, int dest) {
    s->data.d[s->top++] = dest;
}
void pushM(stack* s, char dest) {
    s->data.m[s->top++] = dest;
}
short JudgeMode(char* cmd) {  // 0-invalid; 1-assign; 2-calculate
    char* p = strchr(cmd, '=');
    if (p == NULL) {  // cmd may be a calculating command
        if
    } else {  // cmd may be a assigning command
    }
}
int main() {
    Initialize();
    char cmd[1024];
    while (fgets(cmd, 1024, stdin) != EOF) {
        short mode = JudgeMode(cmd);
    }
    return 0;
}
bool isValid(char* a) {
    int len = strlen(a);
    stack brackets;
    brackets.top = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == '(') {
            pushM(&brackets, a[i]);
        } else if (a[i] == ')' && (brackets.top == 0 || popM(&brackets) !=)) {
            return false;
        }
    }
    return brackets.top == 0;
}