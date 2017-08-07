#include <stdio.h>
#include <malloc.h>

#define MAX_N 100000
#define IS_INVALID(handle) (handle == NULL)

typedef struct node_ {
    int v, i;
    struct node_ *next, *less_elem;
} node;

typedef struct list_ {
    int size;
    node *head, *tail;
} list;

void list_push(list *l, int value, int index, node *less_elem) {
    if (IS_INVALID(l)) return;
    node *tmp = (node *) malloc(sizeof(node));
    tmp->v = value;
    tmp->i = index;
    tmp->next = NULL;
    tmp->less_elem = less_elem;
    if (IS_INVALID(l->head))
        l->head = tmp;
    else
        l->tail->next = tmp;
    l->tail = tmp;
    (l->size)++;
}

typedef struct pack_ {
    int size;
    list data[MAX_N];
} pack;

int bin_search(pack *decks, int value){
    if (decks->size == 0) return -1;
    if (decks->data[0].tail->v > value) return 0;
    if (decks->data[decks->size - 1].tail->v < value) return decks->size;

    int first = 0, last = decks->size - 1, mid;
    while (first != last){
        mid = first + (last - first) / 2;
        if (value <= decks->data[mid].tail->v)
            last = mid;
        else
            first = mid + 1;
    }
    return last;
}

int n, ans[MAX_N], a, pos;
pack decks;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i\n", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i ", &a);
        pos = bin_search(&decks, a);
        if (pos == -1){
            decks.size++;
            pos++;
        } else if (pos == decks.size)
            decks.size++;
        list_push(&decks.data[pos], a, i, (pos > 0) ? (decks.data[pos - 1].tail) : (NULL));
    }
    a = -1;
    printf("%i\n", decks.size);
    for (node *tmp = decks.data[decks.size - 1].tail; !IS_INVALID(tmp); tmp = tmp->less_elem)
        ans[++a] = tmp->i + 1;
    for (int i = a; i >= 0; --i)
        printf("%i ", ans[i]);
    return 0;
}