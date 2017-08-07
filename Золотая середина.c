#include <stdio.h>
#include <malloc.h>

typedef struct _node {
    int val;
} node;

typedef int (*pCompare)(node *, node *);

typedef struct _heap {
    pCompare comparator;
    int size;
    node *root;
} Heap;

void swap(node *a, node *b) {
    node buf = *a;
    *a = *b;
    *b = buf;
}

int less(node *a, node *b) {
    return (a->val < b->val);
}

int more(node *a, node *b) {
    return (a->val > b->val);
}

int heap_create(Heap *h, int size, pCompare cmp) {
    h->comparator = cmp;
    h->size = 0;
    h->root = (node *) malloc(size * sizeof(node));
    return 0;
}

void sift_up(Heap *heap, int index) {
    int parent;
    for(;(index > 0) && (heap->comparator(&(heap->root[index]), &(heap->root[parent = (index - 1) / 2])));) {
        swap(&(heap->root[index]), &(heap->root[parent]));
        index = parent;
    }
}

void sift_down(Heap *heap, int index) {
    for(int child = 2 * index + 1;child < heap->size; child = 2 * index + 1) {
        if (((child + 1) < heap->size) && heap->comparator(&(heap->root[child + 1]), &(heap->root[child])))
            child++;
        if (heap->comparator(&(heap->root[child]), &(heap->root[index]))) {
            swap(&(heap->root[index]), &(heap->root[child]));
            index = child;
        } else break;
    }
}

int heap_push(Heap *h, int val) {
    h->root[h->size].val = val;
    sift_up(h, h->size);
    return ++(h->size);
}

node heap_pop(Heap *h) {
    node min = h->root[0];
    h->root[0].val = h->root[--h->size].val;
    sift_down(h, 0);
    return min;
}

node heap_get_root(Heap *h) {
    return h->root[0];
}

void heap_node_replace(Heap *dist, Heap *source) {
    node buff = heap_pop(source);
    heap_push(dist, buff.val);
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    int n, a, diff;
    scanf("%d", &n);
    Heap *min_heap = (Heap *) malloc(sizeof(Heap)), *max_heap = (Heap *) malloc(sizeof(Heap));
    heap_create(min_heap, n, &(more));
    heap_create(max_heap, n, &(less));

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        if (heap_get_root(min_heap).val >= a)
            heap_push(min_heap, a);
        else
            heap_push(max_heap, a);

        diff = max_heap->size - min_heap->size;
        if (diff < -1)
            heap_node_replace(max_heap, min_heap);
        else if (diff > 0)
            heap_node_replace(min_heap, max_heap);
        printf("%d ", heap_get_root(min_heap).val);
    }
    return 0;
}