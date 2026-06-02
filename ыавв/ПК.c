// task3.c – Потерянные координаты
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 10005

int tree1[MAXVAL * 4], tree2[MAXVAL * 4];

void update(int *tree, int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        if (val > tree[v]) tree[v] = val;
        return;
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) update(tree, v*2, tl, tm, pos, val);
    else update(tree, v*2+1, tm+1, tr, pos, val);
    tree[v] = tree[v*2] > tree[v*2+1] ? tree[v*2] : tree[v*2+1];
}

int query(int *tree, int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l <= tl && tr <= r) return tree[v];
    int tm = (tl + tr) >> 1, res = 0;
    if (l <= tm) {
        int q = query(tree, v*2, tl, tm, l, r);
        if (q > res) res = q;
    }
    if (r > tm) {
        int q = query(tree, v*2+1, tm+1, tr, l, r);
        if (q > res) res = q;
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    int *x = malloc(n * sizeof(int));
    int maxx = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x[i]);
        if (x[i] > maxx) maxx = x[i];
    }
    // инициализация деревьев нулями
    for (int i = 0; i < MAXVAL * 4; ++i) tree1[i] = tree2[i] = 0;
    int last_s = 0;
    for (int i = 0; i < n; ++i) {
        int xi = x[i];
        int max_left = query(tree1, 1, 1, maxx, 1, xi - 1);
        int max_right = query(tree2, 1, 1, maxx, xi, maxx);
        int s = xi + 1;
        if (max_left > s) s = max_left;
        if (max_right > s) s = max_right;
        update(tree1, 1, 1, maxx, xi, s);
        update(tree2, 1, 1, maxx, xi, s + 1);
        last_s = s;
    }
    int yn = last_s - x[n-1];
    printf("%d\n", yn);
    free(x);
    return 0;
}