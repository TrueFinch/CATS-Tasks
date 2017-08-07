#include <stdio.h>

#define MAX_N 100
#define MAX_W 1000000
#define MIN(a, b) a <= b ? a : b

int n, m, u, v, w;
int adj[MAX_N][MAX_N];

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i %i\n", &n, &m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            adj[i][j] = MAX_W;
    for (int i = 0; i < n; ++i)
        adj[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        scanf("%i %i %i\n", &u, &v, &w);
        adj[u - 1][v - 1] = w;
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if((adj[i][k] != MAX_W) && (adj[k][j] != MAX_W))
                    adj[i][j] = MIN(adj[i][j], adj[i][k] + adj[k][j]);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (adj[i][j] != MAX_W)
                printf("%i ", adj[i][j]);
            else
                printf("  ");
        printf("\n");
    }
    return 0;
}