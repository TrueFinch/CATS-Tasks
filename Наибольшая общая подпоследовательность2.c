#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

char a[1001], b[1001], temp[1001];
int c[1002][1002];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    gets(a);
    gets(b);

    if (strlen(a)<strlen(b))
    {
        strcpy(temp, a);
        strcpy(a, b);
        strcpy(b, temp);
    }

    int max_len = strlen(a);
    int min_len = strlen(b);

    for (int i = 0; i<max_len; i++)
    {
        for (int j = 0; j<min_len; j++)
        {
            if (a[i]==b[j])
                c[i+1][j+1] = MAX(MAX(c[i][j]+1, c[i+1][j]),
                                  MAX(c[i][j]+1, c[i][j+1]));
            else
                c[i+1][j+1] = MAX(MAX(c[i][j], c[i+1][j]),
                                  MAX(c[i][j], c[i][j+1]));
        }
    }

    int i = max_len-1, j = min_len-1, size = 0;

    while ((i>=0)&&(j>=0))
    {
        if (c[i+1][j+1]==c[i][j+1])
        {
            i--;
            continue;
        }
        if (c[i+1][j+1]==c[i][j])
        {
            i--;
            j--;
            continue;
        }
        if (c[i+1][j+1]==c[i+1][j])
        {
            j--;
            continue;
        }
        if (c[i+1][j+1]-1==c[i][j])
        {
            if (a[i]==b[j])
                temp[size++] = a[i];
            i--;
            j--;
            continue;
        }

    }

    for (int i = size-1; i>=0; i--)
        printf("%c",temp[i]);

    return 0;
}

