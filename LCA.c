#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define IS_INVALID(handle) (handle == NULL)
#define MAX_N 100020
#define MIN(a, b) (a < b) ? (a) : (b)
#define MAX(a, b) (a > b) ? (a) : (b)

typedef struct _node {
    int v;
    struct _node *next;
} node;

typedef struct _list{
    int size;
    node *head, *tail;
} list;

typedef node *iterator;

void list_push(list *l, int value) {
    if (IS_INVALID(l)) return;
    node *tmp = (node *) malloc(sizeof(node));
    tmp->v = value;
    tmp->next = NULL;
    if (IS_INVALID(l->head))
        l->head = tmp;
    else
        l->tail->next = tmp;
    l->tail = tmp;
    (l->size)++;
}

list *adj;
int first[MAX_N], depth[MAX_N], vertex[2 * MAX_N], order = 0, n, v, u, tree[10 * MAX_N], height = 0, tree_size;
bool used[MAX_N];

void tree_build(int v, int tl, int tr){
    if (tl == tr)
        tree[v] = vertex[tl];
    else {
        int tmid = tl + (tr - tl) / 2;
        tree_build(v * 2, tl, tmid);
        tree_build(v * 2 + 1, tmid + 1, tr);
        tree[v] = (depth[tree[v * 2]] <= depth[tree[v * 2 + 1]]) ? (tree[v * 2]) : (tree[v * 2 + 1]);
    }
}

int tree_min(int v, int tl, int tr, int l, int r){
    if (l > r)
        return INT_MAX;
    if ((l == tl) && (r == tr))
        return tree[v];
    int tmid = tl + (tr - tl) / 2;
    int ans1 = tree_min(v * 2, tl, tmid, l, MIN(tmid, r));
    int ans2 = tree_min(v * 2 + 1, tmid + 1, tr, MAX(tmid + 1, l), r);
    if (ans2 == INT_MAX)
        return ans1;
    if (ans1 == INT_MAX)
        return ans2;
    return (depth[ans1] < depth[ans2]) ? (ans1) : (ans2);
}

void dfs(int v){
    used[v] = true;
    depth[v] = height;
    vertex[order++] = v;
    for (iterator it = adj[v].head; !IS_INVALID(it); it = it->next)
        if (!used[it->v]){
            height++;
            dfs(it->v);
            height--;
            vertex[order++] = v;
        }
}

void preprocess(){
    dfs(0);
    tree_build(1, 0, order - 1);
    for (int i = 0; i < order; ++i)
        if (first[vertex[i]] == -1)
            first[vertex[i]] = i;
}

int LCA(int a, int b){
    int left = MIN(first[a], first[b]),
            right = MAX(first[a], first[b]);
    return tree_min(1, 0, order - 1, left, right);
}

void initialization(int n){
    adj = (list *) malloc(n * sizeof(list));
    for (int i = 0; i < n; ++i){
        adj[i].head = adj[i].tail = NULL;
        adj[i].size = 0;
    }

    for (int i = 0; i < MAX_N; ++i)
        first[i] = -1;

    for (int i = 1; i < 4 * MAX_N; ++i)
        tree[i] = INT_MAX;
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i\n", &n);
    initialization(n);
    for (int i = 0; i < n - 1; ++i){
        scanf("%i%i\n", &v, &u);
        list_push(&(adj[v - 1]), u - 1);
        list_push(&(adj[u - 1]), v - 1);
    }

    preprocess();

    while (scanf("%i%i\n", &v, &u) != EOF)
        printf("%i\n", LCA(v - 1, u - 1) + 1);
    return 0;
}