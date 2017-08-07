#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *input = freopen("diploma.in", "rt", stdin); /*diploma.in input.txt*/
    FILE *output = freopen("diploma.out", "wt", stdout); /*diploma.out output.txt*/

    unsigned long long W, H, N;
    scanf("%I64u%I64u%I64u", &W, &H, &N);
    unsigned long long r, l = 0;
    r = (W+H)*N + 1;


    while (r - l > 1) {
        unsigned long long s = (r - l) / 2 + l;
        if (((s/W) * (s/H)) >= N) r = s;
        else l = s;
    }

    printf("%I64u", r);
    fclose(input);
    fclose(output);
    return 0;
}