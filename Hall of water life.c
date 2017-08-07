#include <stdio.h>
#include <mem.h>
#include <limits.h>

typedef unsigned int uint;

#define MAX_N 400
#define MIN(a, b) ((a <= b) ? (a) : (b))
#define MAX(a, b) ((a >= b) ? (a) : (b))

uint p[MAX_N][MAX_N], n, m, x[MAX_N], dist, new;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    memset(p, 255, MAX_N * MAX_N * sizeof(uint));
    //printf("%u\n", p[0][0]);
    p[0][0] = 0;

    scanf("%u%u\n", &n, &m);
    for (uint i = 0; i < n; ++i) scanf("%u ", &(x[i]));

    for (uint s = 1; s < n; ++s){
        for (uint c = 0; c <= m; ++c){
            new = INT_MAX;
            for (uint k = 0; k <= MIN(m, MIN(s - 1, c)); ++k){
                dist = MAX(p[s - k - 1][c - k], x[s] - x[s - k - 1]);
                new = MIN(new, dist);
            }
            p[s][c] = new;
        }
    }
    printf("%u\n", p[n - 1][m]);
   /* for (int s = 0; s < n; ++s){
        for(int c = 0; c <= m; ++c)
            printf("%u ", p[s][c]);
        printf("\n");
    }*/
    return 0;
}