#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//Макрос
#define max(a,c,x) do {            \
        x = a[0];                   \
        for(int i=0;i<c;i++){        \
            if(a[i]>x){               \
                x = a[i];              \
            }                           \
        }                                \
} while(0)

int main(){
    printf("Введите числа через пробел: \n");
    char temp[256];
    int A[256], k = 0, maks = 0;//Динамический сделать?
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp,'\n')]='\0';
    int *t = strtok(temp," ");
        if(strlen(temp)==0){
            printf("Токенов нет! Плохо... 😰\n");
            return 1;
        }
        while(t != NULL && k<100){
            A[k++] = atoi(t);
            t = strtok(NULL, " ");
        }
        if(k == 0){
            printf("Числе нет! Плохо... или нет... 😵‍💫\n");
            return 1;
        }
        max(A,k, maks);
        printf("Наибольшее: %d \n", maks);
    return 0;
}

