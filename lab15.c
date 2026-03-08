#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int razbivka(int n,int **ar,int *size){
    int temp = n;
    int k = 0;

    if(temp == 0){//Находим кол-во цифр в числе
        k = 1;
    }
    else{
        while(temp!=0){
            k++;
            temp = temp/10;
        }
    }

    *ar = (int*)malloc(k*sizeof(int));

    if(*ar == NULL){
        *size = 0;
        return 1;
    }

    int ind = k-1;
    temp = n;

    if(temp == 0){//В обратном порядке перебираем индексы и записываем цифры
        *ar[0]=0;
    }
    else{
        while(temp !=0){
            (*ar)[ind--] = temp % 10;
            temp = temp/10;
        }
    }
    *size = k;
    return 0;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int *ar;
    int n = 179;
    int size;
    printf("Исходное число: %d\n", n);
    printf("===============================\n");
    if(razbivka(n,&ar,&size)){
        printf("Ошибка! Память не выделена\n");
        return 1;
    }
    printf("Разбивка прямая: ");
        for(int i = 0; i<size; i++){
            printf("%d ", ar[i]);
        }
    return 0;
}