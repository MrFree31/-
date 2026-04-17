#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* bin(int n){
    int id = 0;//шаги для движения по массиву bits
    int bits[32];/*Int (от англ. integer — целое число) — это фундаментальный тип данных в программировании,
                 предназначенный для хранения целых чисел без дробной части. Обычно занимает 4 байта (32 бита) памяти,
                  позволяя хранить значения в диапазоне +-2 миллиарда. */

    //Массив для вывода
    //33 - '\0'
    char *bin_n = (char*)malloc(33 * sizeof(char));

    if(n == 0){
        bin_n[0]='0';
        bin_n[1]='\0';
        return bin_n;
    }

    while(n>0){//Поскольку n - int, результат последующего деления будет сразу обрезаться до запятой, ползволяя отделять целое и остаток.
        bits[id] = n % 2;
        n = n/2;
        id++;
    }
    
    int j = 0;
    for(int i = id-1; i>=0; i--){//Запишем нули и единицы в обратном порядке, как мы это делали бы выписывая из столбика на бумаге
        if(bits[i] == 0){
            bin_n[j] = '0';
            j++;
        }
        else{
            bin_n[j] = '1';
            j++;
        }
        bin_n[j] = '\0';
    }

    return bin_n;
}

int main(){
    int n;
    char schislenie[5];
    printf("Which number? ");
    scanf("%d", &n);
    printf("Which schislenie?(bin...) ");
    scanf(" %s", &schislenie);
    
    if(strcmp(schislenie,"bin") == 0){
        char *binar = bin(n);
        printf("%s\n", binar);
    }
    else{
        printf("There is no else\n");
    }

    return 0;
}