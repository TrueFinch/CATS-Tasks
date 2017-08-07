#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

#define MAX_N 15000
#define MAX_M 20003
#define MAX_LEN 300
#define MAX_K 3003
#define RANDOM_SEED 1046527

int n, m, paletteSize = 0, color = 0, spaces[MAX_K][MAX_K], prev[MAX_N],
        palette[MAX_M], request1, request2;
char garland[MAX_M][MAX_LEN], request[MAX_K];

void q_sort(int *a, int left, int right){
    int i = left, j = right, mid = a[left + rand() % (right - left)];
    do {
        while((strcmp(garland[a[i]], garland[mid]) < 0) && (i < right)) ++i;
        while((strcmp(garland[a[j]], garland[mid]) > 0) && (j > left)) --j;
        if (i <= j){
            int buff = a[i];
            a[i] = a[j];
            a[j] = buff;
            ++i, --j;
        }
    } while (i <= j);
    if (left < j) q_sort(a, left, j);
    if (right > i) q_sort(a, i, right);
}

int binSearch(const char *s, int r) {
    int l = 0, split = 0, c = 0;
    while (l <= r) {
        split = l + (r - l) / 2;
        c = strcmp(garland[palette[split]], s);
        if (c < 0)
            l = split + 1;
        else if (c > 0)
            r = split - 1;
        else
            return split;
    }
    return -1;
}

void init_data() {
    srand(RANDOM_SEED);
    for (int i = 0; i < MAX_K; ++i) {
        for (int j = 0; j < MAX_K; ++j) {
            spaces[i][j] = -1;
        }
    }
    for (int i = 0; i < MAX_M; ++i)
        prev[i] = -1;
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i\n", &n);

    init_data();

    for (int i = 0; i < n; ++i) {
        palette[i] = i;
        gets(garland[i]);
    }

    q_sort(palette, 0, n - 1);

    for (int i = 1; i < n; ++i)
        if (strcmp(garland[palette[paletteSize]], garland[palette[i]]) != 0) {
            palette[++paletteSize] = palette[i];
        }

    for (int i = 0; i < n; ++i) {
        color = binSearch(garland[i], paletteSize);
        for (int j = 0; j <= paletteSize; ++j)
            if ((prev[j] != -1) && ((spaces[color][j] > i - prev[j]) || (spaces[color][j] == -1)))
                spaces[color][j] = spaces[j][color] = i - prev[j];
        prev[color] = i;
    }

    scanf("%i\n", &m);
    for (int i = 0; i < m; ++i) {
        gets(request);
        request1 = binSearch(request, paletteSize);

        gets(request);
        request2 = binSearch(request, paletteSize);

        printf("%i\n", ((request1 < 0) || (request2 < 0)) ? (-1) : (spaces[request1][request2] - 1));
    }
    return 0;
}