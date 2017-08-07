#include <stdio.h>
#include <math.h>

int linear[200000], headl = 0, headt = 0, x, v, n, m;
double time[200000];

void my_qsort(double *array, int left, int right) {
    int i = left, j = right;
    double m = array[(i + j) / 2], buff;
    do {
        while (array[i] < m) ++i;
        while (array[j] > m) --j;
        if (i <= j) {
            buff = array[i];
            array[i] = array[j];
            array[j] = buff;
            ++i;
            --j;
        }
    } while (i <= j);
    if (left < j) my_qsort(array, left, j);
    if (i < right) my_qsort(array, i, right);
}

int main() {
    freopen("linear.in", "r", stdin),
    freopen("linear.out", "w", stdout);
    /*linear.in input.txt
      linear.out output.txt*/

    scanf("%i\n", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i%i\n", &x, &v);
        if (v > 0) {
            linear[headl++] = x;
        } else if (headl != 0) {
                time[headt++] = fabs((double) x - linear[headl - 1]);
                --headl;
            }
    }
    if (headt > 0)
        my_qsort(time, 0, headt - 1);
    scanf("%i\n", &m);
    for (int i = 0, v = 0; i < m; ++i) {
        scanf("%i", &x);
        while((v < headt) && (time[v] <= x*2)){
            n -= 2;
            ++v;
        }
        printf("%i\n", n);
    }
    return 0;
}