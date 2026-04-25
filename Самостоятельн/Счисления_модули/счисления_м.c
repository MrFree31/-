#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perevod.h"
#include "scheslenie.h"

int main(){
    char n[256];
    char schislenie[5];
    printf("Which number(enter with prefixes)?: ");
    scanf("%s", &n);
    int base, sign, minus;
    get_schislenie(n,&base, &sign, &minus);

    printf("Which schislenie?(bin, dec, oct...): ");
    scanf(" %s", &schislenie);
    
    if(strcmp(schislenie,"bin") == 0){
        if(base == 2){
            if(sign == -1) printf("-");//У нас STRING!!! Добавляем минус печатаньем символа!!!
            printf("%s\n",n);
        }
        if(base == 8){
            int dec = oct_dec(n);
            char *binar = dec_bin(abs(dec));// Передаём абсолютное значение, так как dec_bin, dec_oct, dec_hex ожидают неотрицательное число.
            // Знак "-"" выводим отдельно перед результатом (если sign == -1).
            if(sign == -1) printf("-");//SAME!!!
            printf("%s\n", binar);
            free(binar);
        }
        if(base == 10){
            int dec = atoi(n);
            char *binar = dec_bin(abs(dec));
            if(sign == -1) printf("-");//SAME!!!
            printf("%s\n", binar);
            free(binar);
        }
        if(base == 16){
            int dec = hex_dec(n);
            char *binar = dec_bin(abs(dec));
            if(sign == -1) printf("-");//SAME!!!
            printf("%s\n", binar);
            free(binar);
        }
    }
    else if(strcmp(schislenie,"dec") == 0){
        if(base == 2){
            int bin = bin_dec(n)*sign;//Возвращаем int -> можно просто домножить на сам sign
            printf("%d\n", bin);
        }
        if(base == 8){
            int dec = oct_dec(n)*sign;//SAME(1)!!!
            printf("%d\n",dec);
        }
        if(base == 10){
            if(sign == -1) printf("-");//SAME!!!
            printf("%s\n",n);
        }
        if(base == 16){
            int dec = hex_dec(n)*sign;//SAME(1)!!!
            printf("%d",dec);
        }
    }
    else if(strcmp(schislenie, "oct") == 0){
        if(base == 2){
            int dec = bin_dec(n);
            int* oct = dec_oct(dec);
            if(sign == -1) printf("-");//SAME!!!
            for(int i = 0; oct[i]!= -1; i++){
                printf("%d",oct[i]);
            }
            free(oct);
        }
        if(base == 8){
            if(sign == -1) printf("-");//SAME!!!
            for(int i = 0; n[i]!= '\0'; i++){
                printf("%c",n[i]);
            }
        }
        if(base == 10){
            int dec = atoi(n);
            int* oct = dec_oct(dec);
            if(sign == -1) printf("-");//SAME!!!
            for(int i = 0; oct[i]!= -1; i++){
                printf("%d",oct[i]);
            }
            free(oct);
        }
        if(base == 16){
            int dec = hex_dec(n);
            int* oct = dec_oct(dec);
            if(sign == -1) printf("-");//SAME!!!
            for(int i = 0; oct[i]!= -1; i++){
                printf("%d",oct[i]);
            }
            free(oct);
        } 
    }
    else if(strcmp(schislenie, "hex") == 0){
        if(base == 16){
            if(sign == -1) printf("-");
            printf("%s\n",n);
        }else{
            int dec;
            if(base == 2) dec = bin_dec(n);
            if(base == 8) dec = oct_dec(n);
            if(base == 10) dec = atoi(n);
            char *hex = dec_hex(dec);
            if(sign == -1) printf("-");
            printf("%s\n", hex);
            free(hex);
        }
    }
    else{
        printf("There is no other ready\n");
    }
    
    return 0;
}