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

int* dec_oct(int n){
    int id = 0;//шаги для движения по массиву bits
    int nums[32];/*Int (от англ. integer — целое число) — это фундаментальный тип данных в программировании,
                 предназначенный для хранения целых чисел без дробной части. Обычно занимает 4 байта (32 бита) памяти,
                  позволяя хранить значения в диапазоне +-2 миллиарда. */

    //Массив для вывода
    //33 - '\0'
    int *oct_n = (int*)malloc(33 * sizeof(int));

    if(n == 0){
        oct_n[0] = 0;
        oct_n[1] = -1;// '\0' не впишем в int -> нужно -1, так как в остатке -1 не выйдет точно
        return oct_n;
    }

    while(n>0){//Поскольку n - int, результат последующего деления будет сразу обрезаться до запятой, ползволяя отделять целое и остаток.
        nums[id] = n % 8;
        n = n/8;
        id++;
    }
    
    int j = 0;
    for(int i = id-1; i>=0; i--){//Запишем нули и единицы в обратном порядке, как мы это делали бы выписывая из столбика на бумаге   
            oct_n[j] = nums[i];
            j++;
    }
    oct_n[j] = -1;//Тоже самое

    return oct_n;
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

int oct_dec(char* n){
    int k = 0, dec = 0;

    while(n[k]!='\0'){
        k++;
    }
    for(int i = 0; i<k; i++){
        dec += (int) ((n[i]-'0') * pow(8,k-1-i)+0.5);/*В массиве у нас чары, в арифметике они дадут свой код.
        '0' = 48, при вычитании '0' из любого числа выйдет оно само('7' = 55. '7'-'0' = 55 - 48 = 7). atoi типо не круто
        pow - возвращает double, чтобы нивелировать погрешность добавим 0.5 для увеличения на один. Через смену типа обрубаем значения после запятой*/
    }
    return dec;
}

int hex_dec(char* n){
    int k = 0, dec = 0,val;

    while(n[k]!='\0'){
        k++;
    }
    for(int i = 0; i<k; i++){
        if(n[i]>= '0' && n[i] <= '9'){// Индексы вычитаем и получаем наше число
            val = n[i] - '0';
        }
        else if(n[i] >= 'A' && n[i]<='F'){// В шестнадцатиричной системе используются знаки A-F со значениями 10-15. Также вычетаем индесы и прибавляем 10. 'A' - 'A' = 0 + 10 = 10 - наше значение
            val = n[i] - 'A' + 10;
        }
        else if(n[i] >= 'a' && n[i] <= 'f'){//Same
            val = n[i] - 'a' + 10;
        }
        else{
            printf("Ошибка! Посторонние символы в hex-числе\n");
            break;
        }
        dec += val * (int)(pow(16,k-1-i)+0.5);//Нивелирование флоата.
    }
    return dec;
}

int main(){
    char n[256];
    char schislenie[5];
    printf("Which number(enter with prefixes)?: ");
    scanf("%s", &n);
    int base;
    get_schislenie(n,&base);

    printf("Which schislenie?(bin, dec, oct...): ");
    scanf(" %s", &schislenie);
    
    if(strcmp(schislenie,"bin") == 0){
        if(base == 2){
            printf("%s",n);
        }
        if(base == 8){
            int dec = oct_dec(n);
            char *binar = dec_bin(dec);
            printf("%s", binar);
            free(binar);
        }
        if(base == 10){
            int dec = atoi(n);
            char *binar = dec_bin(dec);
            printf("%s\n", binar);
            free(binar);
        }
        if(base == 16){
            int dec = hex_dec(n);
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
        if(base == 8){
            int dec = oct_dec(n);
            printf("%d\n",dec);
        }
        if(base == 10){
            printf("%d",n);
        }
        if(base == 16){
            int dec = hex_dec(n);
            printf("%d",dec);
        }
    }
    else if(strcmp(schislenie, "oct") == 0){
        if(base == 2){
            int dec = bin_dec(n);
            int* oct = dec_oct(dec);
            for(int i = 0; oct[i]!= -1; i++){
                printf("%d",oct[i]);
            }
            free(oct);
        }
        if(base == 8){
            for(int i = 0; n[i]!= '\0'; i++){
                printf("%с",n[i]);
            }
        }
        if(base == 10){
            int dec = atoi(n);
            int* oct = dec_oct(dec);
            for(int i = 0; oct[i]!= -1; i++){
                printf("%d",oct[i]);
            }
            free(oct);
        }
        if(base == 16){
            int dec = hex_dec(n);
            int* oct = dec_oct(dec);
            for(int i = 0; oct[i]!= -1; i++){
                printf("%d",oct[i]);
            }
            free(oct);
        } 
    }
    else{
        printf("There is no other ready\n");
    }
    
    return 0;
}