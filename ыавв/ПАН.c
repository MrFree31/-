// task6.c – Паника
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int h[MAXN];
int left[MAXN], right[MAXN];
int stack[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    // left[i] – ближайший слева строго больший
    int top = 0;
    for (int i = 1; i <= n; ++i) {
        while (top > 0 && h[stack[top - 1]] <= h[i]) --top;
        left[i] = (top == 0) ? -1 : stack[top - 1];
        stack[top++] = i;
    }
    // right[i] – ближайший справа строго больший
    top = 0;
    for (int i = n; i >= 1; --i) {
        while (top > 0 && h[stack[top - 1]] <= h[i]) --top;
        right[i] = (top == 0) ? n + 1 : stack[top - 1];
        stack[top++] = i;
    }
    int ans = 2; // как минимум можно убить двух выстрелами
    for (int i = 1; i <= n; ++i) {
        if (left[i] != -1 && right[i] != n + 1) {
            int len = right[i] - left[i] + 1;
            if (len > ans) ans = len;
        }
    }
    printf("%d\n", ans);
    return 0;
}