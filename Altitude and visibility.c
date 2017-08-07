#include stdio.h
#include stdlib.h
#include math.h
#include limits.h
 
#define MIN(a, b) a = b  a  b
 
typedef struct high_ {
    long h, d;
} height;
 
typedef struct number_ {
    long v, i;
} num;
 
height highs;
num stack;
 
void p(long head, long i, long c)
{
    if(head == -1) {
            ++(head);
            stack[head].v = c;
            stack[head].i = i;
        } else {
            while ((stack[head].v  c) && ((head)  (-1))) {
                    highs[stack[head].i].d = MIN((long)abs((int) i - stack[head].i), highs[stack[head].i].d);
                    --(head);
            }
            ++(head);
            stack[head].v = c;
            stack[head].i = i;
        }
}
 
int main()
{
    freopen(input.txt, rt, stdin);
    freopen(output.txt, wt, stdout);
 
    long n, c, head = -1;
    scanf(%li, &n);
    highs = (height) malloc(nsizeof(height));
    stack = (num) malloc(nsizeof(num));
 
    for(long i = 0; i  n; ++i)
        highs[i].d = LONG_MAX;
    for(long i = 0; i  n; ++i) {
        scanf(%li, &(c));
        highs[i].h = c;
        p(&head, i, c);
    }
    head = -1;
    for(long i = n - 1; i = 0; --i) {
        c = highs[i].h;
        p(&head, i, c);
    }
    for(long i = head; i = 0; --i)
        if(highs[stack[i].i].d == LONG_MAX)
            highs[stack[i].i].d = 0;
 
    for(long i = 0; i  n; ++i)
        printf(%d , highs[i].d);
    free(stack);
    free(highs);
    return 0;
}