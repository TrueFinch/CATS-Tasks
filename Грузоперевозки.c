#include <stdio.h>
#include <stdbool.h>

#define MAX_N 301
#define INF 100000000
#define MIN(a, b) (a <= b) ? (a) : (b)

int n, m, u, v, w, q, adj[MAX_N][MAX_N];
bool used[MAX_N][MAX_N];

void dfs(int k, int i) {
    used[k][i] = true;
    for (int j = 0; j < n; ++j)
        if (!used[k][j] && (adj[i][j] != INF))
            dfs(k, j);
}

void Floyd_Warshall(int adj[MAX_N][MAX_N], int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if ((adj[i][k] != INF) && (adj[k][j] != INF))
                    adj[i][j] = MIN(adj[i][j], adj[i][k] + adj[k][j]);
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i\n", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            adj[i][j] = (i == j) ? (0) : (INF);

    for (int i = 0; i < m; ++i) {
        scanf("%i%i%i\n", &u, &v, &w);
        adj[u - 1][v - 1] = w;
    }

    for (int k = 0; k < n; ++k)
        dfs(k, k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            (used[i][j] && used[j][i]) ? (adj[i][j] = adj[j][i] = 0) : 42;

    Floyd_Warshall(adj, n);

    scanf("%i\n", &q);
    for (int i = 0; i < q; ++i) {
        scanf("%i%i\n", &u, &v);
        printf("%i\n", (adj[--u][--v] == INF) ? (-1) : (adj[u][v]));
    }
    return 0;
}