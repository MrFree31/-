#include <stdio.h>
#include <string.h>
#include "scheslenie.h"

void get_schislenie(char* n, int *base, int *sign, int *minus){
    *minus = 0;
    *sign = 1;
    if(n[0] == '-'){
        *sign = -1;
        *minus = 1;
        int i = 1, j = 0;
        while(n[i] != '\0'){
            n[j] = n[i];
            i++;
            j++;
        }
        n[j] = '\0';
    }
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
