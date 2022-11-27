#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100005
char stack[SIZE] = {'\0'};
int top = 0;
void push(char a) {
    stack[top++] = a;
}
char pop() {
    return stack[--top];
}
bool match(char x, char y) {
    return (x == '(' && y == ')') || (x == '[' && y == ']') ||
           (x == '{' && y == '}');
}
bool isValid(char a[], int len) {
    top = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == '(' || a[i] == '[' || a[i] == '{') {
            push(a[i]);
        } else if (a[i] != ')' && a[i] != ']' && a[i] != '}') {
            return false;
        } else if (top == 0 || !match(pop(), a[i])) {
            return false;
        }
    }
    return top == 0;
}
int main() {
    int T;
    bool mem[50];
    char a[SIZE];
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%s", a);
        mem[i] = isValid(a, strlen(a));
    }
    for (int i = 0; i < T; i++) {
        printf(mem[i] ? "True\n" : "False\n");
    }
    return 0;
}