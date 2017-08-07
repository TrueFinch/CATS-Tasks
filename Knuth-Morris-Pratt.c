#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100001

void prefix_function(char *string, int len, int *p) {
    p[0] = 0;
    for (int i = 1, k = 0; i < len; ++i) {
        k = p[i - 1];
        while ((k > 0) && (string[i] != string[k]))
            k = p[k - 1];
        if (string[k] == string[i])
            ++k;
        p[i] = k;
    }
}

int KMP(int l_haystack, int l_needle, int *p) {
    for (int i = 0; i < l_haystack; ++i)
        if (p[l_needle + i + 1] == l_needle)
            return (i - l_needle + 1);
    return (-2);
}

char haystack[MAX_LENGTH], needle[MAX_LENGTH], sum[MAX_LENGTH * 2], separator[2] = {'#', '\0'};
int p[MAX_LENGTH * 2], l_haystack, l_needle;

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);

    gets(haystack);
    gets(needle);
    l_haystack = strlen(haystack);
    l_needle = strlen(needle);

    strcat(sum, needle);
    strcat(sum, separator);
    strcat(sum, haystack);

    prefix_function(sum, strlen(sum), p);
    printf("%i", KMP(l_haystack, l_needle, p) + 1);
    return 0;
}