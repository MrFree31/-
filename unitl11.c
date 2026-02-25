#include "unitl11.h"
#include <stdarg.h>

void perem_arg(int k, int *sum, int *max, int *min, int *sred, ...){
    va_list argument;
    va_start(argument,sred);

    if (k <= 0){
        printf("Недостаточно аргументов(их нет)\n");
        return 1;
    }
    int x = va_arg(argument, int);
    x = *sum = *max = *min = *sred;

    for(int i = 1; i<k; i++){
        int temp = va_arg(argument, int);
        *sum += temp;
        if(temp > *max) *max = temp;
        if(temp < *min) *min = temp;
    }
    *sred = (double)*sum / k;
    va_end(argument);
}