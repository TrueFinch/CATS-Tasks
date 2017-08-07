#include <stdio.h>

#define MAX_N 1000
#define MAX_W 1000000
#define MIN(a, b) a < b ? a : b

typedef struct _edge {
    int u, v, w;
} edge;

int d[MAX_N], n, m, s, u, v, w;
edge a[MAX_N];

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i %i %i\n", &n, &m, &s);

    for (int i = 0; i < n; ++i)
        d[i] = MAX_W;
    d[s - 1] = 0;

    for (int i = 0; i < m; ++i) {
        scanf("%i %i %i\n", &u, &v, &w);
        a[i].u = u - 1;
        a[i].v = v - 1;
        a[i].w = w;
    }

    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < m; ++j)
            if (d[a[j].u] < MAX_W) {
                d[a[j].v] = MIN(d[a[j].v], d[a[j].u] + a[j].w);
                /*for (int i = 0; i < n; ++i)
                        printf("%i ", d[i]);*/
            }

    for (int i = 0; i < n; ++i) {
        if (d[i] != MAX_W)
            printf("%i ", d[i]);
        else
            printf("  ");
    }


    return 0;
}