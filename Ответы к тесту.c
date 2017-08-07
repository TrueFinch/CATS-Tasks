#include <stdio.h>

#define MAX_Q 15
#define MAX_P 1000
#define TRUE 1
#define FALSE !TRUE

typedef struct {
    int ans[MAX_Q], mark;
} test;

test attempts[MAX_P], solution;
char c;
int P = 0, Q = 0;

void Inc(test *t) {
    t->ans[Q - 1]++;
    for (int i = Q - 1; i > 0; --i)
        if ((t->ans[i]) > 1) {
            t->ans[i] = 0;
            t->ans[i - 1]++;
        } else break;
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    scanf("%i%i\n", &P, &Q);
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < Q; ++j) {
            scanf("%c", &(c));
            attempts[i].ans[j] = ((c == 43) ? (1) : (0));
        }
        scanf("\n%i\n", &(attempts[i].mark));
    }

    for (int correct = TRUE; solution.ans[0] != 2; correct = TRUE, Inc(&(solution))) {
        for(int j = 0, right_ans = 0; j < P; ++j, right_ans = 0){
            for(int k = 0; k < Q; ++k)
                right_ans += (solution.ans[k] == attempts[j].ans[k]) ? 1 : 0;
            if (right_ans != attempts[j].mark){
                correct = FALSE;
                break;
            }
        }
        if(correct){
            for(int j = 0; j < Q; ++j)
                printf("%c", ((solution.ans[j] == 0) ? (45) : (43)));
            break;
        }
    }
    return 0;
}