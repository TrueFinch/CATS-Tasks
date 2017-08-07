#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX_N 1000
#define INF 10000000

typedef struct _node {
    int v, w;
    struct _node *next;
} Node, edge;
typedef struct _list {
    Node *head, *tail;
    int size;
} list;

void init_node(int w, int v, Node *p) {
    p->w = w;
    p->v = v;
    p->next = NULL;
}

void create_list(list *l) {
    l->size = 0;
    l->head = l->tail = NULL;
}

int empty(list *l) {
    return (l->size == 0);
}

void push_back(list *l, Node a) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    *tmp = a;
    if (empty(l))
        l->head = tmp;
    if (l->tail != NULL)
        l->tail->next = tmp;
    l->tail = tmp;
    l->size++;
}

Node get_by_index(list *l, int index) {
    if ((!empty(l)) && (index < l->size)) {
        Node *tmp = l->head;
        for (int i = 0; i < index; ++i)
            tmp = tmp->next;
        return *(tmp);
    }
}

Node pop_front(list *l) {
    if (!empty(l)) {
        Node tmp = *(l->head),
                *p = l->head;
        l->head = l->head->next;
        if (l->head == NULL)
            l->tail = NULL;
        free(p);
        l->size--;
        return tmp;
    }
}

int n, m, s, dist[MAX_N], used[MAX_N];
list graph[MAX_N];
edge tmp;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i%i", &n, &m, &s);


    /*-=-=-= Initialization part =-=-=-*/
    for (int i = 0; i < n; ++i) {
        create_list(&(graph[i]));
        dist[i] = INF;
        used[i] = false;
    }
    dist[s - 1] = 0;
    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%i%i%i\n", &u, &v, &w);
        init_node(w, v - 1, &tmp);
        push_back(&(graph[u - 1]), tmp);
    }

    for (int i = 0; i < n; ++i) {
        int to, v = -1, w;
        for (int j = 0; j < n; ++j)
            if ((!used[j]) && ((v == -1) || (dist[j] < dist[v])))
                v = j;
        if (dist[v] == INF)
            break;
        used[v] = true;

        for(int j = 0; j < graph[v].size; ++j){
            tmp = get_by_index(&(graph[v]), j);
            to = tmp.v;
            w = tmp.w;
            if ((dist[v] + w) < dist[to]){
                dist[to] = dist[v] + w;
            }
        }
    }

    for (int i = 0; i < n; ++i)
        if (dist[i] == INF)
            printf("-1 ");
        else
            printf("%i ", dist[i]);

    return 0;
}