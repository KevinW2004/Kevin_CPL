#include <stdio.h>
int main() {
    unsigned int ui;
    scanf("%x", &ui);
    printf("%d\n%u\n%.6f\n%.3e\n", ui, ui, *((float*)(&ui)), *((float*)(&ui)));
    return 0;
}