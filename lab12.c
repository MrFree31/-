#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int srav(const char *a, const char *b){//strcmp
    while(*a && (*a == *b)){
        *a++,*b++;
    }
    return *(unsigned char*)a-*(unsigned char*)b;
}

int tok(const char *in, int *elem){//Разбивка строк
    char *temp = malloc(strlen(in)+1);
    
    if(temp == NULL){
        printf("Ошибка! Память для токенов не выделилась\n");
        return 1;
    }
    int k = 0;
    strcpy(temp, in);
    char *t = strtok(temp, ".");
    while(t != NULL && k < 3){
        elem[k++] = atoi(t);
        t = strtok(NULL, ".");
    }
    free(temp);
    return k;
}

void now(char *x, size_t size){ //нынешняя дата(now) 
    time_t now = time(NULL);
    struct tm *now_f = localtime(&now);
    
    strftime(x, size, "%d-%m-%Y", now_f);   
}

int dotw(int *e){
    struct tm dayw = {0};
    dayw.tm_year = e[0]-1900;/*отсчёт от 1900, мы берём 2026 или что бы там ни было,
                            если взять просто 2026, то будет 1900 + 2026 = 3926 год. */
    dayw.tm_mon = e[1]-1;//индексы, надо вписаться😒.
    dayw.tm_mday = e[2];
    mktime(&dayw); //Упорядоченье (32 января => 1 февраля и тд.)👍
    return dayw.tm_wday;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    char input[20];
    printf("Введите формат(гггг.мм.дд, ..., now): ");
    fgets(input, sizeof(input),stdin);

    int len = strlen(input);

    if(len>0 && input[len-1] == '\n'){
        input[len-1] = '\0';
    }

    
    if(srav(input, "now") == 0){
        char date[50];
        now(date, sizeof(date));
        printf("Настоящая дата: %s\n", date);
    }
    else{
        int elem[3] = {0}, k = 0;
        k = tok(input, elem);
        if(k == 3){
            int out;
            const char* week[] = {"Воскресенье","Понедельник","Вторник",\ 
                                    "Среда","Четверг","Пятница","Суббота"}; /*tm_wday хранит индекс,
                                    где 0 - воскресенье, как у "западных партнёров"*/
            out = dotw(elem);
            printf("Указаный день: %s\n", week[out]);
        }
    }
    return 0;
}