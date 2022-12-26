#ifndef API
#define API
typedef struct node {
    int val;
    struct node* next;
} Node;
// void FreeList(Node* head);
void Append(Node* head, int val);
void PrintList(Node* head);

// 传入被删除结点的前一个结点（不然寻找上一个结点很麻烦）
void Delete(Node* head, Node* prev);

#endif