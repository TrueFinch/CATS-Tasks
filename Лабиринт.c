#include <stdio.h>
#include <malloc.h>

#define FAlSE 0;
#define TRUE 1;
#define WALL '#'
#define MAX_N 1501

typedef struct _wave{
    int x, y, d;
    struct _wave *next;
} Wave;
typedef struct _queue{
    Wave *head, *tail;
    int size;
} Queue;

void init_wave(int x, int y, int d, Wave *p){
    p->x = x, p->y = y, p->d = d, p->next = NULL;
}

void create_queue(Queue *q){
    q->size = 0;
    q->head = q->tail = NULL;
}

int empty(Queue *q){
    return (q->size == 0);
}

void push(Queue *q, Wave a){
    Wave *tmp = (Wave *)malloc(sizeof(Wave));
    *tmp = a;
    if(empty(q))
        q->head = tmp;
    if(q->tail != NULL)
        q->tail->next = tmp;
    q->tail = tmp;
    q->size++;
}

Wave pop(Queue *q){
    if(!empty(q)){
        Wave tmp = *(q->head),
             *p = q->head;
        q->head = q->head->next;
        if(q->head == NULL)
            q->tail = NULL;
        free(p);
        q->size--;
        return tmp;
    }
}

Wave wave, tmp;
Queue queue;
char maze[MAX_N][MAX_N],
     used[MAX_N][MAX_N];
int n;
int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i\n", &n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%c", &(maze[i][j]));
        }
        scanf("\n");
    }

    used[0][0] = 1;
    init_wave(0, 0 ,0, &wave);
    create_queue(&(queue));
    push(&queue, wave);
    for(;!empty(&queue);){
        wave = pop(&queue);
        if((wave.x >= n - 1) && (wave.y >= n - 1)){
            printf("%i", wave.d);
            return 0;
        }
        if(((wave.x + 1) < n) && (!used[wave.x + 1][wave.y]) && (maze[wave.x + 1][wave.y] != WALL)){
            init_wave(wave.x + 1, wave.y, wave.d + 1, &tmp);
            push(&queue, tmp);
            used[wave.x + 1][wave.y] = TRUE;
        }
        if(((wave.x - 1) > -1) && (!used[wave.x - 1][wave.y]) && (maze[wave.x - 1][wave.y] != WALL)){
            init_wave(wave.x - 1, wave.y, wave.d + 1, &tmp);
            push(&queue, tmp);
            used[wave.x - 1][wave.y] = TRUE;
        }
        if(((wave.y + 1) < n) && (!used[wave.x][wave.y + 1]) && (maze[wave.x][wave.y + 1] != WALL)){
            init_wave(wave.x, wave.y + 1, wave.d + 1, &tmp);
            push(&queue, tmp);
            used[wave.x][wave.y + 1] = TRUE;
        }
        if(((wave.y - 1) > -1) && (!used[wave.x][wave.y - 1]) && (maze[wave.x][wave.y - 1] != WALL)){
            init_wave(wave.x, wave.y - 1, wave.d + 1, &tmp);
            push(&queue, tmp);
            used[wave.x][wave.y - 1] = TRUE;
        }
    }

    printf("%i", -1);
    return 0;
}