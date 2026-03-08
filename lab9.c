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
    char bin = '+';
    int un = 1;
    int znak = 1;
        double r = 0;
        while(t != NULL){
            if(srav_str(t,'+') == 0 || srav_str(t,'-') == 0){
                if(un){
                    if(t[0] =='-'){
                        znak = -1;
                    }
                }
                else{
                    bin = t[0];
                    un = 1;
                }
            }
            else{
                double x = atof(t) * znak;
                znak = 1;

                if(un){
                    r = x;
                }
                else{
                    if(znak == '+'){
                        r += x;
                    }
                    else{
                        r -= x;
                    }
                }
                un = 0;
            }
            t = strtok(NULL," ");
        }
    printf("Результат: %.5lf\n",r);
    return 0;
}