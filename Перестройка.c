/*As the code was wrote...
 *each of lines in their own way was broken.
 *It was hard to know who was more weird.
 *Me... Or everyone else.*/

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define MAX_N 100005
#define MAX_COMP 3
#define MIN(a, b) ((a < b) ? (a) : (b))

typedef unsigned long long t_ull;

typedef struct _dyn_array {
    int size, length;
    int *d;
} dyn_array;

void dyn_array_push(dyn_array *d, int value) {
    d->d[d->length++] = value;
    if (d->size == d->length) {
        d->size *= 2;
        d->d = (int *) realloc(d->d, sizeof(int) * d->size);
    }
}

void dyn_array_initialize(dyn_array *d) {
    d->length = 0;
    d->size = 1;
    d->d = (int *) malloc(sizeof(int));
}

dyn_array adj[MAX_N], bridges;
int n, m, v, u, subTreeSize[MAX_N], components[MAX_COMP], compCount = 0, timeIN[MAX_N], timeOUT[MAX_N], t = 0;
bool used[MAX_N];
t_ull ans;

void comp_dfs(int v) {
    used[v] = true;
    subTreeSize[v] = 1;
    for (int i = 0, u; i < adj[v].length; ++i) {
        u = adj[v].d[i];
        if ((subTreeSize[u] == 0) && (!used[u])) {
            comp_dfs(u);
            subTreeSize[v] += subTreeSize[u];
        }
    }
}

void find_components() {
    for (int i = 0; i < n; ++i) {
        used[i] = false;
        subTreeSize[i] = 0;
    }
    for (int i = 0; (i < n) && (compCount <= 2); ++i)
        if (!used[i]) {
            comp_dfs(i);
            components[compCount++] = subTreeSize[i];
        }
}

void bridge_dfs(int v, int parent) {
    used[v] = true;
    timeIN[v] = timeOUT[v] = ++t;
    for (int i = 0, u = 0; i < adj[v].length; ++i) {
        u = adj[v].d[i];
        if (u == parent) {
            continue;
        } else if (!used[u]) {
            bridge_dfs(u, v);
            timeOUT[v] = MIN(timeOUT[v], timeOUT[u]);
            if (timeOUT[u] > timeIN[v])
                dyn_array_push(&bridges, subTreeSize[u]);
        } else {
            timeOUT[v] = MIN(timeOUT[v], timeIN[u]);
        }
    }
}

void find_bridges() {
    for (int i = 0; i < n; ++i) {
        used[i] = false;
        timeIN[i] = timeOUT[i] = 0;
    }
    for (int i = 0; (i < n) && (compCount <= 2); ++i)
        if (!used[i])
            bridge_dfs(i, -1);
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i\n", &n, &m);

    for (int i = 0; i < n; ++i) {
        dyn_array_initialize(&(adj[i]));
    }

    for (int i = 0; i < m; ++i) {
        scanf("%i%i\n", &v, &u);
        dyn_array_push(&(adj[--v]), --u);
        dyn_array_push(&(adj[u]), v);
    }

    find_components();

    dyn_array_initialize(&bridges);

    find_bridges();

    if (compCount == 1) {
        ans = (t_ull) n * (t_ull) (n - 1) / 2 - (t_ull) m;
        ans *= (m - bridges.length);
        for (int i = 0; i < bridges.length; ++i)
            ans += (t_ull) ((n - bridges.d[i]) * (t_ull) bridges.d[i] - 1);
        printf("%lli\n", ans);
    } else if (compCount == 2) {
        ans = (t_ull) components[0] * (t_ull) components[1];
        ans *= (t_ull) (m - bridges.length);
        printf("%lli\n", ans);
    } else
        printf("%i\n", 0);

    return 0;
}