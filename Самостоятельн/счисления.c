#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void get_schislenie(char* n, int *base){
    if(n[0]=='0'){
        //Двоичная
        if(n[1] == 'b'|| n[1] == 'B'){
            *base = 2;
            int k = 2;
            while(n[k] != '\0'){
                n[k-2] = n[k];
                k++;
            }
            n[k-2] = '\0';
        }
        //Шестнадцатиричная
        else if(n[1] == 'x'|| n[1] == 'X'){
            *base = 16;
            int k = 2;
            while(n[k] != '\0'){
                n[k-2] = n[k];
                k++;
            }
            n[k-2] = '\0';
        }
        else{
            //Восьмиричная
            *base = 8;
            int k = 1;
            while(n[k] != '\0'){
            n[k-1] = n[k];
            k++;
            }
            n[k-1] = '\0';
        }        
    }
    else{
        *base = 10;
    }
}

char* dec_bin(int n){
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

int bin_dec(char* n){
    int k = 0, dec = 0;
    
    while(n[k] != '\0'){//Берём длину строки для перевода, там типо степени по индексам выбираются
        k++;
    }
    for(int i = 0; i<k; i++){
        if(n[i]=='1'){
            dec += 1*pow(2,k-1-i);
        }
        if(n[i]=='0'){
            dec += 0*pow(2,k-1-i);
        }
    }
    return dec;
}

char* bin_oct(char* n){
    int k = 0;
    char* oct = (char*)malloc(256 * sizeof(char));
    char* troyka = (char*)malloc(4 * sizeof(char));//В восьмиричную переводят перебирая тройки битов.

    while(n[k] != '\0'){//Берём длину строки для перевода, там типо степени по индексам выбираются
        k++;
    }
    for(int i = 0; i<k; i++){
        int temp = 0;
        if(n[i]=='1'){
            temp += 1*pow(2,k-1-i); 
        }
        if(n[i]=='0'){
            temp += 0*pow(2,k-1-i);
        }
    }
    return oct;

}

int main(){
    char n[256];
    char schislenie[5];
    printf("Which number(enter with prefixes)? ");
    scanf("%s", &n);
    int base;
    get_schislenie(n,&base);

    printf("Which schislenie?(bin, dec...) ");
    scanf(" %s", &schislenie);
    
    if(strcmp(schislenie,"bin") == 0){
        if(base == 10){
            int dec = atoi(n);
            char *binar = dec_bin(dec);
            printf("%s\n", binar);
            free(binar);
        }
    }
    else if(strcmp(schislenie,"dec") == 0){
        if(base == 2){
            int bin = bin_dec(n);
            printf("%d\n", bin);
        }
    }
    else{
        printf("There is no other ready\n");
    }

    

    return 0;
}