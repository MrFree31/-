#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
int isvowel(int c){
    switch (tolower((unsigned char)c))
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'y': return 1;
    }
    return 0;
}

//int main(int argc, char **argv){ - Остатки былых цивилизаций
int main(){
    SetConsoleOutputCP(CP_UTF8);
    char input[50];

    printf("Введите имя файла: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    FILE *f1;
    f1=fopen(input,"r");
    if(f1 == NULL){
        printf("Ошибка! Файл %s не прочитан - ПРОПУСКАЕМ \n",input);
        return 1;
    }

    printf("Файл %s открыт\n", input);//ОТЛАДКА😒, не читалось. (Нужно было в VScode отдельно сохранять файл перед компиляцией👿)

    int c, letter, cons, vowel, string, lower, upper, digit, space, punct, total = 0;
    total=letter=string=lower=upper=punct=cons=digit=space=vowel=0;

    while((c=fgetc(f1))!=EOF){
        total++;

        if(c == '\n') string++;
        else if(isspace(c)) space++;
        else if(ispunct(c)) punct++;   
        else if (isalpha(c)){
            letter++;
            if(isvowel(c)) vowel++;
            else cons++;
            if(islower(c)) lower++;
            else if(isupper(c)) upper++;
        }

        else if(isdigit(c)) digit++;  
    }

fclose(f1);
printf("FILE %s: total=%d, letters=%d, vowels=%d, cons=%d, string=%d,\n lower=%d, upper=%d, digits=%d,\
spaces=%d, puncts=%d,\n",input,total,letter,vowel,cons,string,lower,upper,digit,space,punct);
printf("\n");
    return 0;
}
/*Тестировал на файлах, которые в папке с лабораторной на сайте лежали, перепроверял через блокнот кол-во строк. 
В блокноте всегда на 1 больше, чем при пересчёте через "\n". Но заданию такой пересчёт соответствует. ¯\(°_o)/¯ */