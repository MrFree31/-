#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 1000

int comp(const void *a, const void *b){//На вход любые данные вводим - нужно для qsort
    int a_int = *(int*)a;//превращаем в нужную переменную
    int b_int = *(int*)b;
    return (a_int > b_int) - (a_int < b_int); //классический метод сравнения
}

int main(){
    int capacity = MAX;
    int *input = (int*)malloc(capacity*sizeof(int));
    
    SetConsoleOutputCP(CP_UTF8);

    FILE *f = fopen("sortir.txt", "r");
    if(f == NULL){
        perror("Ошибка! чтения sortir.txt");
        return 1;
    }

    int k = 0;//Счётчик считываемых строк
    int full = 0;
    while(fscanf(f, "%d", &input[k]) == 1){
        k++;
        if(k == capacity){//Добрались до конца массива
            full++;
            printf("Полон %d\n", full);
            capacity *= 2;
            int *temp = realloc(input, capacity * sizeof(int));//Дополняем массив после переполнения
            if(temp == NULL){
                perror("Ошибка перераспределения памяти");
                free(input);
                fclose(f);
                return 1;
            }
            input = temp;
        }
    }
    fclose(f);

    if(k == 0){
        printf("sortir.txt пуст\n");
        return 0;
    }
    /*Самая магия. Даём массив, кол-во элементов внутри, сколько данных брать,
    сама функция не знает формат данных, поэтому мы даём на обработку объём данных,
    свойственный переменной данного типа, А ПОТОМ ФУНКЦИЮ В АРГУМЕНТ!!!!*/
    qsort(input, k, sizeof(int), comp);//быстрая сортировка! O(n log n)

    FILE *f2 = fopen("sortir_out.txt", "w");
    if(f2 == NULL){
        perror("Ошибка! записи sortir_out.txt");
        return 1;
    }

    for(int i = 0; i<k; i++){
        fprintf(f2, "%d\n", input[i]);
    }

    fclose(f2);
    free(input);
    printf("Отсортированно %d чисел, проверяй sortir_out.txt\n",k);
    return 0;
}
