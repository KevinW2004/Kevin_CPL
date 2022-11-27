#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int space;
    int data;
    struct Node* next;
} node;
node* head;
int cnt = 1;  // Number of nodes.
void printList() {
    node* p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    putchar('\n');
}
void InsertNode(node* new, node* pre) {
    new->next = pre->next;
    pre->next = new;
    cnt++;
}
void split(node* p, int m, int id) {
    p->space = p->space / 2;
    node* new = (node*)malloc(sizeof(node));
    InsertNode(new, p);
    new->space = p->space;
    new->data = 0;
    if (p->space > m) {
        split(p, m, id);
    } else {
        p->data = id;
    }
}
void findMem(int m, int id) {
    node* p = head;
    while (p->space < m || p->data != 0)
        p = p->next;
    if (p->space == m) {
        p->data = id;
    } else {
        split(p, m, id);
    }
}
//找到大于等于m的最小2的幂次方
int standardize(int m) {
    int sum = 1;
    while (sum < m)
        sum *= 2;
    return sum;
}
int main() {
    head = (node*)malloc(sizeof(node));
    int n, q;
    char cmd[10005][100] = {'\0'};
    int id, m;
    scanf("%d%d", &n, &q);
    head->space = pow(2, n);
    head->data = 0;
    head->next = NULL;
    getchar();
    for (int k = 0; k < q; k++) {
        fgets(cmd[k], 100, stdin);
    }
    for (int k = 0; k < q; k++) {
        if (cmd[k][0] == 'Q') {
            printf("%d\n", cnt);
            printList();
        } else if (cmd[k][0] == 'A') {
            int i = 1;
            id = 0;
            m = 0;
            while (cmd[k][++i] >= '0' && cmd[k][i] <= '9')
                id = id * 10 + (cmd[k][i] - '0');
            while (cmd[k][++i] >= '0' && cmd[k][i] <= '9')
                m = m * 10 + (cmd[k][i] - '0');
            m = standardize(m);
            findMem(m, id);
        }
    }
    return 0;
}