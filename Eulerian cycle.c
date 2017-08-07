#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define MAX_N 100000
#define IS_INVALID(handle) ((handle == NULL) ? (true) : (false))

typedef struct _edge {
    int v;
    struct _edge *next, *last, *twin;
} edge;
typedef struct _list {
    edge *head, *tail;
    int size;
} list;

int list_empty(list *l) {
    return (l->size == 0) ? (true) : (false);
}

edge *list_push(list *l, edge e) {
    if (!IS_INVALID(l)) {
        edge *tmp = (edge *) malloc(sizeof(edge));
        *tmp = e;
        tmp->last = tmp->next = tmp->twin = NULL;
        if (l->head == NULL) {
            l->head = tmp;
        } else {
            tmp->last = l->tail;
            l->tail->next = tmp;
        }
        l->tail = tmp;
        (l->size)++;
    }
    return l->tail;
}

void list_pop(list *l, edge *current) {
    if ((IS_INVALID(l)) || (list_empty(l)) || (IS_INVALID(current)))
        return;
    if (!(IS_INVALID(current->last)) && !(IS_INVALID(current->next))){
        current->last->next = current->next;
        current->next->last = current->last;
    } else if (!(IS_INVALID(current->last))) {
        current->last->next = NULL;
        l->tail = current->last;
    } else if (!(IS_INVALID(current->next))) {
        current->next->last = NULL;
        l->head = current->next;
    }
    free(current);
    (l->size)--;
}

edge *curr, *twin1, *twin2;
int n, m, v, u, deg[MAX_N], stack[MAX_N], size = 1;
list *adj[MAX_N];

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    scanf("%i%i\n", &n, &m);

    for (int i = 0; i < n; ++i) {
        adj[i] = (list *) malloc(sizeof(list));
        adj[i]->head = adj[i]->tail = NULL;
        adj[i]->size = 0;
    }
    curr = (edge *) malloc(sizeof(edge));

    for (int i = 0; i < m; ++i) {
        scanf("%i%i ", &v, &u);
        curr->v = u - 1;
        twin1 = list_push(adj[v - 1], *curr);
        curr->v = v - 1;
        twin2 = list_push(adj[u - 1], *curr);
        adj[v - 1]->tail->twin = twin2;
        adj[u - 1]->tail->twin = twin1;
        deg[v - 1]++;
        deg[u - 1]++;
    }

    for (int i = 0; i < n; ++i)
        if ((deg[i] % 2) == 1) {
            printf("-1");
            return 0;
        }

    free(curr);
    while (size > 0) {
        u = stack[size - 1];
        if (deg[u] == 0) {
            size--;
            printf("%i ", u + 1);
        } else {
            if (adj[u]->size == 0)
                continue;
            curr = adj[u]->head;
            stack[size++] = curr->v;
            (deg[u])--;
            (deg[curr->v])--;
            list_pop(adj[curr->v], curr->twin);
            list_pop(adj[u], curr);
        }
    }
    return 0;
}