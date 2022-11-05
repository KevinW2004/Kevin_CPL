#include <stdio.h>
void readMatrix(int* a, int row, int col) {
    for (int m = 0; m < row; m++) {
        for (int n = 0; n < col; n++) {
            scanf("%d", &*(a + 105 * m + n));
        }
    }
    return;
}
int main() {
    int m, n, p;
    int A[105][105] = {0}, B[105][105] = {0}, C[105][105] = {0};
    scanf("%d %d %d", &m, &n, &p);
    readMatrix(A[0], m, n);
    readMatrix(B[0], n, p);
    for (int row = 0; row < m; row++) {
        for (int col = 0; col < p; col++) {
            for (int k = 0; k < n; k++) {
                C[row][col] += A[row][k] * B[k][col];
            }
            printf("%d ", C[row][col]);
        }
        printf("\n");
    }
    return 0;
}