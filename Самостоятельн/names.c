#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 128 

typedef struct person{
    char name[64];
    int age;
}person;

int comp(person *a, person *b){
    for(int i = 0; a->name[i] || b->name[i]; i++){// a->name[i] || b->name[i] - пока хотя бы один из элементов не ноль - '\0'
        int diff = tolower((unsigned char)a->name[i]) - tolower((unsigned char)b->name[i]);//Кодировки разные коды символов имеют(включая отрицательные), поэтому приводим к беззнаковому char.
        if(diff){//Положит./отриц. значение - символы не равны
            return diff;
        }
        return 0;//символы равны
    }
}

int main(int argc, char *argv[]){
    person *names = NULL;
    int k = 0;//Счётчик обхода
    int capacity = 0;
    char line[LINE_SIZE];
    FILE *f_out = fopen("names_s.txt", "r+");//Проверяем содержание выходного файла

    if(f_out != NULL){//Проверяем содержание выходного файла
        while(fgets(line, LINE_SIZE, f_out)){
            line[strcspn(line, "\n")] = '\0';

            person TEMP;//Структура для передачи данных в основной массив

            if(sscanf(line, "%64s %d", TEMP.name, &TEMP.age) == 2){//Если в строке два параметрп, функция типо возвращает кол-во элементов
                if(k >= capacity){//Проверка переполнения массива
                    capacity = capacity ? capacity * 2 : 4; //Расширяем ёмкость. Тернарный(3 элемента) оператор: ёмкость = (если ёмкость не нулевая(capacity) - 4, иначе домножаем на 2.)
                    names = realloc(names, capacity * sizeof(person)); //Дополняем основной массив в зависимости от размера capacity
                    if(!names){//Память не выделилась
                        perror("Error! Reallocation for main array");
                        fclose(f_out);
                        return 1;
                    }
                }
                //После проверки ёмкости и выделения памяти
                    names[k++] = TEMP;//Запись в основной массив
            }
        }
    }
    
    if(argc>1){//Чтение из файла
        FILE *f_in = fopen(argv[1], "r");
        if(!f_in){
            perror("Error! Opening input file");
            return 1;
        }
        else{
            while(fgets(line, LINE_SIZE, f_in)){
                line[strcspn(line, "\n")] = '\0';
                person TEMP;
                if(sscanf(line, "%64s, %d", TEMP.name, &TEMP.age) == 2){
                    int insert = 0;//Позиция вставки
                    while(insert<k && comp(&names[insert], &TEMP) <= 0){//пока не переполнили и наше значение не больше нуля(нужно пройти те, которые меньше и равны, только потом вставлять)
                        insert++;
                    }
                    

                }

            }
            
        }
    }


    return 0;
}