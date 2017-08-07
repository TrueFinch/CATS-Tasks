#include <stdio.h>
#include <malloc.h>

#define FALSE 0;
#define TRUE 1;
#define MAX_N 100001

typedef struct _node {
    int name, d;
    struct _node *next;
} Node;
typedef struct _list {
    Node *head, *tail;
    int size;
} List;

void init_node(int d, int name, Node *p) {
    p->d = d;
    p->name = name;
    p->next = NULL;
}

void create_list(List *l) {
    l->size = 0;
    l->head = l->tail = NULL;
}

int empty(List *l) {
    return (l->size == 0);
}

void push_back(List *l, Node a) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    *tmp = a;
    if (empty(l))
        l->head = tmp;
    if (l->tail != NULL)
        l->tail->next = tmp;
    l->tail = tmp;
    l->size++;
}

Node get_by_index(List *l, int index) {
    if ((!empty(l)) && (index < l->size)) {
        Node *tmp = l->head;
        for (int i = 0; i < index; ++i)
            tmp = tmp->next;
        return *(tmp);
    }
}

Node pop_front(List *l) {
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

Node wave, tmp;
List queue, adj[MAX_N];
int answer[MAX_N];
char used[MAX_N];
int n, m, s, u, v, ans_size = 0;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i%i\n", &n, &m, &s);
    for (int i = 0; i < n; ++i)
        create_list(&(adj[i]));

    for (int i = 0; i < m; ++i) {
        scanf("%i%i\n", &u, &v);
        tmp.name = v;
        push_back(&(adj[u]), tmp);
        tmp.name = u;
        push_back(&(adj[v]), tmp);
    }

    used[s] = TRUE;
    init_node(0, s, &tmp);
    create_list(&queue);
    push_back(&queue, tmp);
    for (; !empty(&queue);) {
        wave = pop_front(&queue);
        answer[ans_size++] = wave.name;
        for (int i = 0; i < adj[wave.name].size; ++i) {
            tmp = get_by_index(&(adj[wave.name]), i);
            if (!used[tmp.name]) {
                tmp.d = wave.d + 1;
                push_back(&queue, tmp);
                used[tmp.name] = TRUE;
            }
        }
    }
    if (ans_size != n)
        printf("%i", -1);
    else
        for (int i = 0; i < ans_size; ++i)
            printf("%i ", answer[i]);
    return 0;
}