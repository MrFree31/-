// task2.c – Среда обитания
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct { int h, idx; } Node;
Node arr[MAXN];
int occupied[MAXN];
int left[MAXN], right[MAXN]; // для BIT не нужны

// BIT для суммы занятых
int bit[MAXN];
int n, k;

void bit_update(int i, int delta) {
    while (i <= n) {
        bit[i] += delta;
        i += i & -i;
    }
}
int bit_query(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}
int range_sum(int l, int r) {
    if (l > r) return 0;
    return bit_query(r) - bit_query(l - 1);
}

int cmp_desc(const void *a, const void *b) {
    return ((Node*)b)->h - ((Node*)a)->h;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i].h);
        arr[i].idx = i;
    }
    qsort(arr + 1, n, sizeof(Node), cmp_desc);
    for (int i = 1; i <= n; ++i) bit[i] = 0;
    int res[MAXN], cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int pos = arr[i].idx;
        // проверяем, можно ли посадить орла на pos
        int l = pos - k, r = pos - 1;
        if (l < 1) l = 1;
        if (range_sum(l, r) > 0) continue;
        l = pos + 1; r = pos + k;
        if (r > n) r = n;
        if (range_sum(l, r) > 0) continue;
        // подходит
        res[cnt++] = pos;
        bit_update(pos, 1);
    }
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i)
        printf("%d%c", res[i], (i == cnt - 1) ? '\n' : ' ');
    return 0;
}