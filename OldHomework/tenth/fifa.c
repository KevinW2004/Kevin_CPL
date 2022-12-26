#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;
typedef struct team {
    char name[21];
    int score[11][3];  // no need for saving player's name
    double ave[3];
} Team;
Team* teams = NULL;
void getTeam(int i);
void swap(Team* a, Team* b);
void Sort(int q);
int main() {
    scanf("%d", &n);
    teams = (Team*)malloc(n * sizeof(Team));
    for (int i = 0; i < n; i++) {
        getTeam(i);
    }
    for (int i = 0; i < 3; i++) {
        Sort(i);
        putchar('\n');
    }
    return 0;
}
// functions
void getTeam(int i) {
    scanf("%s", teams[i].name);
    char tmp[20];
    memset(teams[i].ave, 0.0, sizeof(teams[i].ave));
    for (int k = 0; k < 11; k++) {
        scanf("%s%d%d%d", tmp, &teams[i].score[k][0], &teams[i].score[k][1],
              &teams[i].score[k][2]);
        for (int j = 0; j < 3; j++)
            teams[i].ave[j] += teams[i].score[k][j];
    }
    for (int j = 0; j < 3; j++)
        teams[i].ave[j] /= 11;
}
void swap(Team* a, Team* b) {
    Team tmp = *a;
    *a = *b;
    *b = tmp;
}
void Sort(int q) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (teams[j].ave[q] > teams[j - 1].ave[q])
                swap(&teams[j], &teams[j - 1]);
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%s ", teams[i].name);
    }
}