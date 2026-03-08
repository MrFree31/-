#include "unitl11.h"
#include <stdio.h>
#include <windows.h>
//gcc lab11.c unitl11.c -o lab11
int main(){
    SetConsoleOutputCP(CP_UTF8);
    int k = 5,sum=0,max=0,min=0;
    double sred=0;
    perem_arg(k,&sum,&max,&min,&sred,9,5,65,12,25);
    printf("Армгументов-%d, сумма=%d, наибольшее=%d, наименьшее=%d, среднее=%.2lf\n",k,sum,max,min,sred);
    return 0;
}
