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

int dotw(int *e){
    struct tm dayw = {0};
    dayw.tm_year = e[0]-1900;/*отсчёт от 1900, мы берём 2026 или что бы там ни было,
                            если взять просто 2026, то будет 1900 + 2026 = 3926 год. */
    dayw.tm_mon = e[1]-1;//индексы, надо вписаться😒.
    dayw.tm_mday = e[2];
    mktime(&dayw); //Упорядоченье (32 января => 1 февраля и тд.)👍
    return dayw.tm_wday;
}

void month(int year, int month){
    int dni[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int d = dni[month - 1];
    if (month == 2 && ((year%4 == 0 && year%100 != 0) || (year%400 == 0))){ //Високосность☺️
        d = 29;
    }
    
    int fotm = dotw((int[]){year,month,1});
    const char *mes[] = {"Янв","Фев","Мар","Апр", "Май","Июнь","Июль","Авг","Сент","Окт","Нояб","Дек"};
    printf("%s %d\n",mes[month-1],year);
    printf("Пн Вт Ср Чт Пт Сб Вс\n");
    int ots = (fotm + 6) % 7;
    for(int i = 0; i<ots;i++){
        printf("   ");
    }
    for(int i = 1;i<=d;i++){
        printf("%3d", i);
        if((ots + i) % 7 == 0){
            printf("\n");
        }
    }
}

void now(char *x, size_t size){ //нынешняя дата(now) 
    time_t now = time(NULL);
    struct tm *now_f = localtime(&now);
    
    strftime(x, size, "%d-%m-%Y", now_f);   
}



int main(){
    int out;
    SetConsoleOutputCP(CP_UTF8);
    char input[20];
    printf("Введите формат(гггг.мм.дд,гггг.мм, гггг, now): ");
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
            
            const char* week[] = {"Воскресенье","Понедельник(Hate mondays😾)","Вторник",
                                    "Среда","Четверг","Пятница","Суббота"}; /*tm_wday хранит индекс,
                                    где 0 - воскресенье, как у "западных партнёров"*/
            out = dotw(elem);
            printf("Указаный день: %s\n", week[out]);
        }
        else if(k == 2){
            if(elem[1]<1||elem[1]>12){
                printf("Нет такого месяца(За пределами 1 и 12)\n");
                return 1;
            }
            month(elem[0],elem[1]);
        }

        else if(k == 1){
            if (elem[0] < 1 || elem[0] > 9999) {
                printf("Год должен быть в диапазоне 1–9999.\n");
                return 1;
            }
            printf("======================\n");
            for(int m = 1;m<=12;m++){
                month(elem[0],m);
                printf("\n");
                printf("======================\n");
                
            }
            
        }

        else{
            printf("Ошибка! Ввод не корректный!(Нужно: гггг.мм.дд,гггг.мм, гггг, now)");
            return 1;
        }
    }
    return 0;
}