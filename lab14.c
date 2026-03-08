#include <stdio.h>
#include <setjmp.h>
#include <windows.h>
long long sum; /*Глобальная переменная, потому что longjmp локальную сломает😁👍(😡),
                не приравняли к нулю её потому, 
                что глобальная автоматом обнуляется или как-то так😁*/
long long fib_l(int N){//Крайнее число в последовательности
    if(N<=2){
        return 1;
    } //...(начиная с1, 1,...)...
    return fib_l(N-2)+fib_l(N-1);
}

/*Сумма крайних, понижая N до 1 } = сумме последовательности Фибоначчи😁👍. 
Рекурсия и потом мы выпригиваем через longjmp (jmp - типо прыжок!!!!(jump))*/
void sum_fib_l(int N, jmp_buf *b){
    if(N==1){
        sum += fib_l(1);
        longjmp(*b, 1);
    }
    sum += fib_l(N);
    sum_fib_l(N-1,b);
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    jmp_buf buf;
    int N;
    printf("Введите N для вычисления суммы чисел Фибоначчи: ");
    scanf("%d",&N);
    if(setjmp(buf)==0){
        sum_fib_l(N,&buf);
    }
    else{
        printf("Сумма %d чисел Фибоначчи = %lld", N, sum);
    }
    
    return 0;
}