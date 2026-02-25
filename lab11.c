#include "unitl11.h"
#include <stdio.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int k = 5,sum=0,max=0,min=0,sred=0;
    perem_arg(k,&sum,&max,&min,&sred,9,5,65,12,25);
    printf("Армгументов: сумма=%d,наибольшее=%d,наименьшее=%d,среднее=%d,%lf\n",k,sum,max,min,sred);
}
