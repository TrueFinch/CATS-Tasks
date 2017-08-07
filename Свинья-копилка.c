#include <stdio.h>
#include <mem.h>
#include <malloc.h>

typedef struct {
    int c, w;
} coin;

#define MAX_INT 2147483647
#define MAX_N 101
#define MIN(a, b) ((a) <= (b)) ? (a) : (b)

coin m[MAX_N];
int f, e, n, *d, min;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i%i\n", &e, &f, &n);
    for (int i = 1; i <= n; ++i)
        scanf("%i%i\n", &(m[i].c), &(m[i].w));
    d = (int *) malloc((f - e + 1) * sizeof(int));
    memset(d, -1, (f - e + 1) * sizeof(int));
    d[0] = 0;

    for (int c = 1; c <= (f - e + 1); ++c) {
        min = MAX_INT;
        for (int i = 1; i <= n; ++i)
            if ((c - m[i].w < 0) || (d[c - m[i].w]) == -1)
                continue;
            else
                min = MIN(min, d[c - m[i].w] + m[i].c);
        if (min == MAX_INT)
            d[c] = -1;
        else
            d[c] = min;
    }
    printf("%i ", d[f - e]);
    return 0;
}