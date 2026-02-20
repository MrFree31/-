#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

int srav_str(const char *a, const char *b){
    while (*a && (*a==*b)){
        *a++,*b++;
    }
    return *(unsigned char*)a-*(unsigned char*)b;
}

//Форматирование строки
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
            if(i>0){
                b[o++] = ' ';
            }
            b[o++] = temp[i];
            b[o++] = ' ';
        }
        else{
            b[o++] = temp[i];
        }
    }
    b[o] = '\0'; //нуль-терминатор в конце строки🤖
}

int main(){
    setConsoleOutputCP(CP_UTF8);
    char A[100];
    printf("Введите выражение: \n");
    fgets(A,sizeof(A),stdin);
    A[strcspn(A,'\n')]='\0';//индекс переноса строки
    if(strlen(A) == 0){
        printf("Пустая строка!\n");
        return 1;
    }

    char B[100];
    ishod(A,B);
    char *t = strtok(B, " ");
    if(t == NULL){
        printf("Ошибка! Токенов нет🪘\n");
        return 1;
    }
        double r = 0;
        while(t != NULL){
            if(srav_str(t,'+') == 0 || srav_str(t,'-') == 0){
                if()
            }
        }
    return 0;
}