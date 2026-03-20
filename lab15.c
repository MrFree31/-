#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int razbivka_pr(int n){
    if(n<10){
        printf(" %d ", n);
    }
    else{
        razbivka_pr(n/10);
        printf("%d ", n%10);
    }
}

int razbivka_ob(int n){
    if(n<10){
        printf("%d ",n);
    }
    else{
        printf("%d ", n%10);
        razbivka_ob(n/10);
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int n = 179;
    printf("Исходное число: %d\n", n);
    printf("===============================\n");

    printf("Разбивка прямая: ");
    razbivka_pr(n);
    printf("\nРазбивка обратная: ");
    razbivka_ob(n);
    return 0;
}