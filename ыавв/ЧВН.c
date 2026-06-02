// task1.c – Чаепитие в небоскребе
#include <stdio.h>
#include <stdlib.h>

typedef struct { int floor; int idx; } Pair;

int cmp_floor(const void *a, const void *b) {
    return ((Pair*)a)->floor - ((Pair*)b)->floor;
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    Pair *pairs = malloc(n * sizeof(Pair));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        pairs[i].floor = a[i];
        pairs[i].idx = i;
    }
    qsort(pairs, n, sizeof(Pair), cmp_floor);
    long long *prefix = malloc((n + 1) * sizeof(long long));
    prefix[0] = 0;
    for (int i = 0; i < n; ++i)
        prefix[i + 1] = prefix[i] + pairs[i].floor;
    long long total = prefix[n];
    long long best_sum = 1LL << 62;
    int best_idx = n + 1;
    for (int i = 0; i < n; ++i) {
        long long left = (long long)i * pairs[i].floor - prefix[i];
        long long right = (total - prefix[i + 1]) - (long long)(n - 1 - i) * pairs[i].floor;
        long long cur = left + right;
        if (cur < best_sum || (cur == best_sum && pairs[i].idx < best_idx)) {
            best_sum = cur;
            best_idx = pairs[i].idx;
        }
    }
    printf("%d\n", best_idx + 1);
    free(a); free(pairs); free(prefix);
    return 0;
}