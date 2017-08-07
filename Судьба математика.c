#include <stdio.h>
#include <memory.h>
#define LIMQT 30
#define NUMSIZE 6
#define FALSE 0
#define TRUE 1
typedef struct _limitation {
    int l, r, sign;
} Lim;
/*-=-=-= incrementing our number =-=-=-*/
int inc(int *a) {
    a[NUMSIZE - 1]++;
    for (int i = NUMSIZE - 1; i > 0; --i)
        if (a[i] >= 10) {
            a[i - 1]++;
            a[i] = 0;
        } else break;
    return 0;
}
Lim Rations[LIMQT];
int Number[NUMSIZE];
int rtn = 0, ans = 0, correct_number = TRUE;

int main() {
    freopen("input.txt", "rt", stdin), freopen("output.txt", "wt", stdout);
    /*-=-=-= Read the input data =-=-=-*/
    memset(Rations, 255, sizeof(Lim) * LIMQT);
    for (char c = '*'; !feof(stdin); c = (char) getc(stdin)) {
        if (c == '\n')rtn++;
        else if ((c >= '0') && (c <= '9')) {
            if (Rations[rtn].l == -1) Rations[rtn].l = c - '1';
            else Rations[rtn].r = c - '1';
        } else if ((c >= '<') && (c <= '>'))                                           /*1  < | 2  = | 3 > */
            if (Rations[rtn].sign == -1) Rations[rtn].sign = c - '<' + 1;              /*4 <= | 5 <> | 6 >=*/
            else Rations[rtn].sign += 3;
    }
    /*-=-=-= Looking for correct variants of number =-=-=-*/
    for (;Number[0] != 10; ans += correct_number ? 1 : 0, inc(Number), correct_number = TRUE) {
        for (int j = 0; (j <= rtn) && (correct_number == TRUE); ++j)
            switch (Rations[j].sign) {
                case 1: if (Number[Rations[j].l] >= Number[Rations[j].r])correct_number = FALSE;
                        break;
                case 2: if (Number[Rations[j].l] != Number[Rations[j].r])correct_number = FALSE;
                        break;
                case 3: if (Number[Rations[j].l] <= Number[Rations[j].r])correct_number = FALSE;
                        break;
                case 4: if (Number[Rations[j].l] > Number[Rations[j].r]) correct_number = FALSE;
                        break;
                case 5: if (Number[Rations[j].l] == Number[Rations[j].r])correct_number = FALSE;
                        break;
                case 6: if (Number[Rations[j].l] < Number[Rations[j].r]) correct_number = FALSE;
                        break;
                default:;
            }
    }
    printf("%i", ans);
    return 0;
}