#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX 1000

int comp(const void *a, const void *b){//На вход любые данные вводим - нужно для qsort
    int a_int = *(int*)a;//превращаем в нужную переменную
    int b_int = *(int*)b;
    return (a_int > b_int) - (a_int < b_int); //классический метод сравнения
}

int main(){
    clock_t start = clock();
    int capacity = MAX;
    int *input = (int*)malloc(capacity*sizeof(int));
    if(input == NULL){
        perror("Ошибка! Выделение input");
        return 1;
    }


    int forward = 0;
    
    SetConsoleOutputCP(CP_UTF8);

    FILE *f = fopen("sortir.txt", "r");
    if(f == NULL){
        perror("Ошибка! чтения sortir.txt");
        return 1;
    }

    printf("Прямой порядок сортировки или обратный?(0/1)\n");

    while(scanf("%d", &forward) != 1 || (forward != 0 && forward != 1)){
        printf("Вводи 0 или 1\n");
        while(getchar() != '\n');
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

    if(forward == 1){
        for(int i = 0; i<k/2; i++){
            int TEMP = input[i];
            input[i] = input[k - 1 - i];
            input[k - 1 - i] = TEMP;
        }

    }

    int unic = 0;//Перебор O(n)
    for(int i = 0; i<k; i++){
        if(i == 0 || input[i] != input[i-1]){
            input[unic++] = input[i];
        }
    }

    if(unic < k){
        printf("Встретились дубли: %d шт\n", k - unic);
        k = unic;//Когда прошли по массиву "к" обрубаем по оставшемуся хвосту => работаем в этом пределе.
    }
    else{
        printf("Дублей нет\n");
    }

    char out[50];
    if(forward == 1){
        sprintf(out, "sortir_r.txt");
    }
    else{
        sprintf(out, "sortir_f.txt");
    }

    FILE *f2 = fopen(out, "w");
    if(f2 == NULL){
        perror("Ошибка! записи");
        return 1;
    }

    for(int i = 0; i<k; i++){
        fprintf(f2, "%d\n", input[i]);
    }



    fclose(f2);
    free(input);
    clock_t end = clock();
    printf("Время выполнения: %.3f секунд\n", (double)(end - start)/CLOCKS_PER_SEC); //CLOCK_PER_SEC - МАКРОС ИЗ БИБЛИОТЕКИ TIME ДЛЯ ПРЕОБРАЗОВАНИЯ ТИКОВ, КОТОРЫЕ И СЧИТАЕТ код.
    printf("Отсортированно %d чисел, проверяй sortir_out.txt\n",k);

    if(k == 1){
        printf("В файле всего одно число: %d\n", input[0]);
        printf("Число %d является одновременно и максимумом, и минимумимом\n", input[0]);
    }
    else if(k>0){
        long long sum = 0;
        for(int i = 0; i<k; i++){
            sum += input[i];
        }
        printf("Минимум: %d\n",input[0]);
        printf("Максимум: %d\n",input[k-1]);
        printf("Сумма чисел: %lld\n", sum);
    }
    else{
        printf("0 элементов (Макс, мин, сумм - нет)\n");
    }
    return 0;
}
