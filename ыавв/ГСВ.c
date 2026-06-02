// task7.c – Гриф с весами
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(long long*)a - *(long long*)b;
}

int main() {
    int n;
    long long M;
    scanf("%d %lld", &n, &M);
    long long *w = malloc(n * sizeof(long long));
    int m = 0;
    for (int i = 0; i < n; ++i) {
        long long x;
        scanf("%lld", &x);
        if (x <= M) w[m++] = x;
    }
    qsort(w, m, sizeof(long long), cmp);
    long long reach = 0;
    int cnt = 0;
    int i = 0;
    while (reach < M) {
        if (i < m && w[i] <= reach + 1) {
            reach += w[i];
            ++i;
        } else {
            // докупаем гирю весом reach+1
            ++cnt;
            reach = 2 * reach + 1;
        }
    }
    printf("%d\n", cnt);
    free(w);
    return 0;
}