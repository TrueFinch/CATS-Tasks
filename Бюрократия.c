#include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE !TRUE
#define MAX 100000

typedef enum {
    WHITE,
    GREY,
    BLACK,
}COLOR;
typedef struct {
    int *adj;
    int arr_size, ref_size;
    COLOR color;
} vertex;
typedef struct{
    int *data;
    int size;
} ans_stack;

vertex *graph;
int dfs(int i);
ans_stack answer;
char unfit[MAX + 1];

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    int n = 0, m = 0;
    scanf("%i%i", &n, &m);

    graph = (vertex *) malloc((n + 1) * sizeof(vertex));
    answer.data = (int *) malloc(n * sizeof(int));
    answer.size = 0;
    for(int i = 1; i <= n; ++i){
        graph[i].adj = NULL;
        graph[i].arr_size = graph[i].ref_size = 0;
        graph[i].color = WHITE;
    }
    int p = 0, c = 0;
    for(int i = 0; i < m; ++i){
        scanf("%i%i", &p, &c);
        if (graph[c].adj == NULL){
            graph[c].adj = (int *) malloc(sizeof(int)*1);
            graph[c].arr_size = 1;
        } else if (graph[c].arr_size == graph[c].ref_size){
            int new_size = graph[c].arr_size * 2;
            graph[c].adj = (int *) realloc(graph[c].adj, new_size * sizeof(int));
            graph[c].arr_size = new_size;
        }

        graph[c].adj[graph[c].ref_size++] = p;
        unfit[p] = TRUE;
        /*for(int k = 1; k <= n; ++k){
            if (graph[k].ref_size != 0){
                printf("%i | ", k);
                for(int j = 0; j < graph[k].ref_size; ++j){
                    printf("%i ", graph[k].adj[j]);
                }
            }
            printf("\n");
        }*/
    }

    for(int i = 1; i <= n; ++i){
        if (!unfit[i]){
            dfs(i);
        }
    }

    if (answer.size == n){
        for(int i = 0; i < answer.size; ++i)
            printf("%i ", answer.data[i]);
    } else
        printf("%i", -1);
    return 0;
}

int dfs(int i) {
    if(graph[i].color ==  GREY) {
//        printf("%i", i);
        return FALSE;
    }
    if(graph[i].color ==  BLACK)
        return TRUE;
    if(graph[i].ref_size == 0){
        answer.data[answer.size++] = i;
        graph[i].color = BLACK;
        return TRUE;
    }
    graph[i].color = GREY;
    for(int j = 0; j < graph[i].ref_size; ++j){

        if (dfs(graph[i].adj[j]) == FALSE)
            return FALSE;
    }
    graph[i].color = BLACK;
    answer.data[answer.size++] = i;
    return TRUE;
}