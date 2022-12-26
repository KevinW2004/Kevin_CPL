#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char name[11];
    struct node* left;
    struct node* right;
    struct node* father;
    int num;  // 以此结点为根结点的树的节点个数
} Node;
Node* root = NULL;
Node* getNode(char* name, Node* n) {  // 找到名字是name的结点
    if (n == NULL)
        return NULL;
    if (strcmp(n->name, name) == 0)
        return n;
    Node* tmp = getNode(name, n->right);
    return tmp != NULL ? tmp : getNode(name, n->left);
}
void rmNode(Node* x) {
    int n = x->num;
    if (x->father->left == x)
        x->father->left = NULL;
    else
        x->father->right = NULL;
    while ((x = x->father) != NULL)
        x->num -= n;
    // freeNode();？好麻烦不写了
}
int main() {
    int n, q;
    root = (Node*)malloc(sizeof(Node));
    root->left = NULL;
    root->right = NULL;
    root->father = NULL;
    root->num = 1;
    scanf("%d%d", &n, &q);
    char s1[11], s2[11];
    for (int i = 0; i < n; i++) {
        scanf("%s%s", s1, s2);
        if (i == 0) {
            strcpy(root->name, s1);
        } else {
            Node* pre = getNode(s2, root);
            Node* new = (Node*)malloc(sizeof(Node));
            strcpy(new->name, s1);
            new->left = NULL;
            new->right = NULL;
            new->father = pre;
            new->num = 1;
            if (pre->right == NULL)
                pre->right = new;
            else
                pre->left = new;
            while ((new = new->father) != NULL)
                new->num++;
        }
    }
    for (int i = 0; i < q; i++) {
        scanf("%s%s", s1, s2);
        if (strcmp(s1, "remove") == 0) {
            rmNode(getNode(s2, root));
        } else if (strcmp(s1, "query") == 0) {
            printf("%d\n", getNode(s2, root)->num);
        }
    }
    return 0;
}