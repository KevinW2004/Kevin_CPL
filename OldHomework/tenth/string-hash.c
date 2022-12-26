#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 61129
int hash(char* s) {
    int len = strlen(s);
    int ret = 0;
    for (int i = 0; i < len; i++)
        ret = (ret + s[i] * (i + 1)) % N;
    return ret;
}
typedef struct node {
    char str[1005];
    struct node* next;
} Node;
Node* head[N] = {NULL};
bool FindStr(char* s) {
    Node* tmp = head[hash(s)];
    while (tmp != NULL) {
        if (strcmp(tmp->str, s) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}
int main() {
    int m, q;
    char s[1005];
    scanf("%d%d", &m, &q);
    for (int i = 0; i < m; i++) {
        scanf("%s", s);
        int h = hash(s);
        Node* tmp = head[h];
        if (tmp == NULL) {
            head[h] = (Node*)malloc(sizeof(Node));
            strcpy(head[h]->str, s);
            head[h]->next = NULL;
        } else {
            while (tmp->next != NULL)
                tmp = tmp->next;
            Node* new = (Node*)malloc(sizeof(Node));
            strcpy(new->str, s);
            tmp->next = new;
            new->next = NULL;
        }
    }
    for (int i = 0; i < q; i++) {
        scanf("%s", s);
        printf(FindStr(s) ? "Yes\n" : "No\n");
    }
    return 0;
}