#include "API.h"
#include <stdio.h>
#include <stdlib.h>
/* void FreeList(Node* head) {
    // TODO
} */
void Append(Node* head, int val) {
    Node* new = malloc(sizeof(*new));
    if (new == NULL) {
        printf("Error: malloc failed in Append()");
        return;
    }
    new->val = val;
    new->next = NULL;
    Node* p = head;
    if (p == NULL) {
        head = new;
    } else {
        while (p->next != NULL)
            p = p->next;
        p->next = new;
    }

    return;
}
void PrintList(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d\n", p->val);
        p = p->next;
    }
}
void Delete(Node* head, Node* prev) {
    Node* cur = prev->next;
    prev->next = prev->next->next;
    free(cur);
}