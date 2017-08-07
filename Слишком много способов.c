#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3000
#define MAGIC 1000000007

int triangle[MAX_SIZE];

int get_num_of_comb(int n, int  m){
    for (int j = 0; j < MAX_SIZE; ++j)
            triangle[j] = 0;
    triangle[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j >= 1; --j) {
                triangle[j] = (triangle[j] + triangle[j - 1]) % MAGIC;
        }
    }
    return triangle[m] % MAGIC;
}

int dx, dy, dz;
long long first_mpl, second_mpl;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    {
        int x1, y1, z1, x2, y2, z2;
        scanf("%i%i%i%i%i%i", &x1, &y1, &z1, &x2, &y2, &z2);
        dx = abs(x2 - x1);
        dy = abs(y2 - y1);
        dz = abs(z2 - z1);
    }

    first_mpl = get_num_of_comb(dx + dy, dy);
    second_mpl = get_num_of_comb(dx + dy + dz, dz);

    printf("%lli", first_mpl * second_mpl * ((dx | dy | dz) != 0) % MAGIC);
    return 0;
}