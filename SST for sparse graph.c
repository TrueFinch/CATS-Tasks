#pragma comment (linker, "/STACK:64000000")

#include <stdio.h>
#include <malloc.h>

#define MAX_EDGES 100000
#define MAX_NODES MAX_EDGES
/*-=-=-=DSU realization=-=-=-*/
int parent[MAX_NODES], rank[MAX_NODES];

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void dsu_make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int dsu_find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = dsu_find_set(parent[v]);
}

void dsu_union_sets(int a, int b) {
    a = dsu_find_set(a);
    b = dsu_find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(&a, &b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

/*-=-=-=---------------=-=-=-*/
typedef struct _edge {
    int u, v, w;
} edge, Data;

void my_qsort(Data *array, int left, int right) {
    int i = left, j = right, m = array[(i + j) / 2].w;
    Data buff;
    do {
        while (array[i].w < m) i++;
        while (array[j].w > m) --j;
        if (i <= j) {
            buff = array[i];
            array[i] = array[j];
            array[j] = buff;
            ++i;
            --j;
        }
    } while (i <= j);
    if (left < j) my_qsort(array, left, j);
    if (i < right) my_qsort(array, i, right);
}

int n, m, u, v, w, length = 0, checker = 0;
edge *e;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i\n", &n, &m);
    e = (edge *) malloc(m * sizeof(edge));
    for (int i = 0; i < m; ++i) {
        scanf("%i%i%i\n", &u, &v, &w);
        e[i].u = u - 1;
        e[i].v = v - 1;
        e[i].w = w;
    }

    for (int i = 0; i < n; ++i)
        dsu_make_set(i);

    my_qsort(e, 0, m);

    for (int i = 0; i < m; ++i) {
        u = e[i].u;
        v = e[i].v;
        w = e[i].w;
        if (dsu_find_set(u) != dsu_find_set(v)) {
            length += w;
            dsu_union_sets(u, v);
        }
    }

    for (int i = 0; i < n; ++i)
        if (parent[i] == i)
            checker++;

    if (checker > 1)
        printf("-1");
    else
        printf("%i", length);

    return 0;
}