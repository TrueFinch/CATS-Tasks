#include <stdio.h>
#include <mem.h>

#define LENGTHOFSEQ 1001
#define MAX(a, b) ((a > b) ? (a) : (b))

char seq1[LENGTHOFSEQ], seq2[LENGTHOFSEQ], result[LENGTHOFSEQ];
int c[LENGTHOFSEQ][LENGTHOFSEQ], z, size = 0;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    gets(seq1);
    gets(seq2);
    int len1 = strlen(seq1), len2 = strlen(seq2);

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            z = (seq1[i - 1] == seq2[j - 1]) ? (1) : (0);
            c[i][j] = MAX((c[i - 1][j - 1] + z), MAX(c[i][j - 1], MAX(c[i - 1][j], c[i - 1][j - 1])));


        }
    }
    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j)
            printf("%i ", c[i][j]);
        printf("\n");
    }
    for (int i = len1, j = len2; (i >= 0) && (j >= 0);) {
        if (c[i][j] == c[i - 1][j])
            --i;
        else if (c[i][j] == c[i - 1][j - 1]) {
            --i;
            --j;
        } else if (c[i][j] == c[i][j - 1])
            --j;
        else if ((c[i][j] - 1) == c[i - 1][j - 1]) {
            if (seq1[i - 1] == seq2[j - 1])
                result[size++] = seq1[i - 1];
            --i;
            --j;
        }
    }
    for (int i = size - 1; i >= 0; --i)
        printf("%c", result[i]);
    return 0;
}