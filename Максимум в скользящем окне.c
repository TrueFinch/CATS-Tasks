#include <stdio.h>

#define RIGHT 82
#define LEN 100005

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    long long n, r = 0, l = 0, head = 0, size = 0;
    scanf("%lld\n", &n);
    long long lArr[LEN], Max[LEN];
    for (long i = 0; i < n; ++i)
        scanf("%lld", &(lArr[i]));
    Max[size++] = 0;
    scanf("%lld\n", &n);
    char c;
    for (long long i = 0; i < n; ++i) {
        scanf("%c", &c);
        if(c == RIGHT){
            ++r;
            for(;(size > 0) && (lArr[Max[head + size - 1]] <= lArr[r]);) --size;
            Max[head + (size++)] = r;
        }
        else {
            if((size > 0) && (Max[head] == l)){
                --size;
                ++head;
            }
            ++l;
        }
        printf("%lld ", lArr[Max[head]]);
    }
    _fcloseall();
    return 0;
}