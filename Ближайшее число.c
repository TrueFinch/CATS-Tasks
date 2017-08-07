#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
struct number {
    long i, v;
};
 
int main()
{
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    long N, *num, head = 0;
    struct number *stack;
 
    scanf("%li", &N);
 
    stack = (struct number*) malloc(N*sizeof(struct number));
    num = (long*) malloc(N*sizeof(N));
 
    for(int i=0; i < N; ++i) {
        long c=0;
        scanf("%li", &c);
        if(head == 0) {
            stack[head].v = c;
            stack[head].i = i;
            ++head;
        } else {
            while((c > stack[head-1].v)&&(head >= 0)) {
                num[stack[head-1].i] = c;
                --head;
            }
            stack[head].v = c;
            stack[head].i = i;
            ++head;
        }
    }
    for(int i=head - 1; i >= 0; --i)
        num[stack[i].i] = stack[i].v;
    for(int i=0; i < N; ++i)
        printf("%li ", num[i]);
    return 0;
}