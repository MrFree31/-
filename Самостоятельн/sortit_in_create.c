#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    FILE *f = fopen("sortir.txt","w");
    for(int i = 0; i<1001; i++){
        fprintf(f,"%d\n", rand() % 10000); //Огранчимся 0-9999 чтобы лимиты для int не переступить
    }
    fclose(f);
    return 0;
}