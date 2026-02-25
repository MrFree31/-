#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void zb(unsigned char *b, int i) {
    b[i / 8] |= (1 << (i % 8));
}


void ub(unsigned char *b, int i) {
    b[i / 8] &= ~(1 << (i % 8));
}


int pb(unsigned char *b, int i) {
    return (b[i / 8] >> (i % 8)) & 1;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);//Кодировка для VScode(В командной строке не проверял)
    int n=0,rb = (n+8)/8,p=2,k=0;
    //rb - размер в байтах с запасом (индексы от нуля)
    printf("Предел поиска чисел n: ");//Запрос предела
    scanf("%d",&n);

    if(n < 2){
        printf("Нет простых в данных пределах (%d)\n",n);
        return 1;
    }

    unsigned char *b = (unsigned char*)malloc(rb);
    if(b == NULL){
        printf("Кто-то напартачил с массивом b!\n");
        return 1;
    }
    for (int i = 0; i < rb; i++) { //перебор байтов
        b[i] = 0xFF; //Все биты в байте = 1
    }
    ub(b,0),ub(b,1);
    
    printf("Подбор простых чисел(предел - %d)\n",n);

    while (p*p<=n){
        if(pb(b,p)){
            for(int i = p*p; i<=n; i += p){ //Стираем кратные
                ub(b,i);
            }
        }
        p++;
    }
    printf("\nПростые числа в пределе %d: ",n);//вывод чисел
    for(int i = 2; i<=n; i++){
        if(pb(b,i)){
            printf("%d ",i);
            k++;
        }
    }
    printf("\n");
    printf("Простых чисел: %d\n",k);
    free(b);
    return 0;
}