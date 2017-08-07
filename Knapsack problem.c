#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define MAX_N 41
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

int n, w, **a, weight[MAX_N], ans[MAX_N];

void restorePath(int k, int s) {
    if (a[k][s] == 0)
        return;
    if (a[k - 1][s] == (a[k][s]))
        restorePath(k - 1, s);
    else {
        restorePath(k - 1, s - weight[k]);
        ans[k] = 1;
    }
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i\n", &n, &w);
    a = (int **) malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; ++i)
        scanf("%i", &(weight[i]));
    for (int i = 0; i <= n; ++i) {
        a[i] = (int *) malloc((w + 1) * sizeof(int));
        memset(a[i], 0, (w + 1) * sizeof(int));
    }

    for (int k = 1; k <= n; ++k)
        for (int s = 1; s <= w; ++s)
            if (s >= weight[k])
                a[k][s] = MAX(a[k - 1][s], a[k - 1][s - weight[k]] + weight[k]);
            else
                a[k][s] = a[k - 1][s];

    if (a[n][w] == w) {
        restorePath(n, w);
        for (int i = 1; i <= n; ++i)
            printf("%i ", ans[i]);
    } else
        printf("-1");
    return 0;
}
