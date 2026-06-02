// task4_5.c – Параллелепипед (суммы на гранях)
#include <stdio.h>

typedef long long ll;

int main() {
    ll nx, ny, nz;
    scanf("%lld %lld %lld", &nx, &ny, &nz);
    // грань X=0
    ll s_x0 = nx * ny * ny * (nz - 1) * nz / 2
            + nx * nz * (ny - 1) * ny / 2
            + ny * nz;
    // грань X=nx-1
    ll s_x1 = s_x0 + (nx - 1) * ny * nz;
    // грань Y=0
    ll s_y0 = nx * nx * ny * (nz - 1) * nz / 2
            + nz * (nx - 1) * nx / 2
            + nx * nz;
    // грань Y=ny-1
    ll s_y1 = s_y0 + (ny - 1) * nx * nx * nz;
    // грань Z=0
    ll s_z0 = nx * nx * (ny - 1) * ny / 2
            + ny * (nx - 1) * nx / 2
            + nx * ny;
    // грань Z=nz-1
    ll s_z1 = s_z0 + (nz - 1) * nx * nx * ny * ny;
    ll sums[6] = {s_x0, s_x1, s_y0, s_y1, s_z0, s_z1};
    // сортировка пузырьком для 6 элементов
    for (int i = 0; i < 5; ++i)
        for (int j = i + 1; j < 6; ++j)
            if (sums[i] > sums[j]) {
                ll t = sums[i]; sums[i] = sums[j]; sums[j] = t;
            }
    for (int i = 0; i < 6; ++i)
        printf("%lld%c", sums[i], (i == 5) ? '\n' : ' ');
    return 0;
}