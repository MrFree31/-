#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ishod(const char *a, char *b){
    char temp[100];
    int t = 0;
    for (int i = 0; a[i]; i++){
        if(a[i] != ' '){
            temp[t++] = a[i];
        }
    }
    temp[t]='\0'; //нуль-терминатор в конце строки🤖

    int o = 0;
    for(int i = 0; temp[i]; i++){
        if(temp[i] =='+'|| temp[i] =='-'){
            b[o++] = temp[i];
        }
    }
    b[o] = '\0';
}
