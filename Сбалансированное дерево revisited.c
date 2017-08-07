#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TABLESIZE 999983
#define MAX_N 1000000
#define IS_INVALID(handle) ((handle == NULL))

typedef struct node_ {
    int v;
    struct node_ *next;
} node;

typedef struct list_ {
    int size;
    node *head, *tail;
} list;


typedef struct hashtable_ {
    list data[TABLESIZE];
} hashtable;


void list_push(list *l, int value) {
    if (IS_INVALID(l)) return;
    for (node *curr = l->head; !IS_INVALID(curr); curr = curr->next)
        if (curr->v == value)
            return;
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

void list_pop(list *l, int value) {
    if (IS_INVALID(l)) return;
    for (node *curr = l->head, *prev = NULL; !IS_INVALID(curr); prev = curr, curr = curr->next) {
        if (curr->v == value){
            if (!IS_INVALID(prev))
                prev->next = curr->next;
            else
                l->head = curr->next;
            free(curr);
            return;
        }
    }
}

int hash(int key, int size){
    return ((key) % size);
}

void hashtable_push(hashtable  *ht, int key){
    list_push(&(ht->data[hash(key, TABLESIZE)]), key);
}

void hashtable_pop(hashtable *ht, int key){
    list_pop(&(ht->data[hash(key, TABLESIZE)]), key);
}

int comparator(const void *a, const void *b){
    return ( *((int *)a) - *((int *)b));
}

int d = 0, len = 0, arr[MAX_N];
hashtable *ht;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    ht = (hashtable *) malloc(sizeof(hashtable));
    for (int i = 0; i < TABLESIZE; ++i){
        ht->data[i].head = ht->data[i].tail = NULL;
        ht->data[i].size = 0;
    }

    while ((scanf("%i ", &d) != EOF) && (d != 0))
        (d > 0) ? (hashtable_push(ht, d)) : (hashtable_pop(ht, -d));

    for (int i = 0; i < TABLESIZE; ++i)
        for (node *tmp = ht->data[i].head; !IS_INVALID(tmp); tmp = tmp->next)
            arr[len++] = tmp->v;
    qsort(arr, (size_t ) len, sizeof(int), comparator);

    for (int i = 0; i < len; ++i)
        printf("%i ", arr[i]);
    return 0;
}