#include <stdio.h>
#include <malloc.h>

typedef int Data;
int n;
void my_qsort(Data *array, int left, int right) {
    for (int i = 0; i < n; ++i)
        printf("%i ", array[i]);
    printf("\n");
    int i = left, j = right, m = array[(i + j) / 2];
    Data buff;
    do {
        while (array[i] < m) i++;
        while (array[j] > m) --j;
        if (i <= j){
            buff = array[i];
            array[i] = array[j];
            array[j] = buff;
            ++i; --j;
            /*for (int i = 0; i < n; ++i)
                printf("%i ", array[i]);
            printf("\n");*/
        }
    } while (i <= j);
    if (left < j) my_qsort(array, left, j);
    if (i < right) my_qsort(array, i, right);
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    //int n;
    scanf("%i", &n);
    Data *array = (Data *) malloc(n * sizeof(Data));
    for (int i = 0; i < n; ++i)
        scanf("%i", &(array[i]));
    for (int i = 0; i < n; ++i)
        printf("%i ", array[i]);
    printf("\n");
    my_qsort(array, 0, n - 1);
    for (int i = 0; i < n; ++i)
        printf("%i ", array[i]);
    return 0;
}