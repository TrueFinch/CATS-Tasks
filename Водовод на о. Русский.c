#include <stdio.h>
#include <stdbool.h>
#include <mem.h>

#define PIPE '#'
#define MAX_SIZE 201
#define MAX_PATH MAX_SIZE * MAX_SIZE

typedef struct _point {
    int x, y;
} Point;

typedef struct _path {
    Point p[MAX_PATH];
    int d;
} Path;

bool reverse = false;
int h, w, ans_count = 0;
Path tmp, ans[2];
char bottom[MAX_SIZE][MAX_SIZE], used[MAX_SIZE][MAX_SIZE];

void dfs(int x, int y) {
    if ((ans_count == 2) || (x >= h) || (x < 0) || (y >= w) || (y < 0) || (bottom[x][y] != PIPE) || used[x][y])
        return;
    used[x][y] = true;
    tmp.p[tmp.d].x = x, tmp.p[tmp.d++].y = y;
    if (y == (w - 1))
        if ((ans_count == 0) || (tmp.d != ans[0].d) || (memcmp(tmp.p, ans[0].p, tmp.d * sizeof(Point)) != 0)) {
            memcpy(ans[ans_count].p, tmp.p, tmp.d * sizeof(Point));
            ans[ans_count++].d = tmp.d;
        }
    if (!reverse) {
        dfs(x + 1, y);
        dfs(x, y + 1);
        dfs(x - 1, y);
        dfs(x, y - 1);
    } else {
        dfs(x, y - 1);
        dfs(x - 1, y);
        dfs(x, y + 1);
        dfs(x + 1, y);
    }
    tmp.d--;
}

void initUsed() {
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            if (used[i][j])
                used[i][j] = false;
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i\n", &h, &w);
    for (int i = 0; i < h; ++i, scanf("\n"))
        for (int j = 0; j < w; ++j)
            scanf("%c", &(bottom[i][j]));
    tmp.d = 0;
    for (int i = 0; i < h; ++i) {
        if (bottom[i][0] == PIPE) {
            reverse = false;
            dfs(i, 0);

            reverse = true;
            initUsed();
            tmp.d = 0;
            dfs(i, 0);
        }
        initUsed();
        tmp.d = 0;
    }

    if (ans_count > 0) {
        if (ans_count == 1)
            printf("YES\n");
        else
            printf("MULTIPLE\n");
        for (int i = 0; (ans[i].d != 0) && (i < 2); ++i, printf("\n")) {
            printf("%i  ", ans[i].d);
            for (int j = 0; j < ans[i].d; ++j) {
                printf("%i %i  ", ans[i].p[j].x + 1, ans[i].p[j].y + 1);
            }
        }
    } else printf("NO");

    return 0;
}