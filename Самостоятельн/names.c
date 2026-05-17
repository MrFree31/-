#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 128 

typedef struct person{
    char name[64];
    int age;
}person;

int comp(person *a, person *b, int sort){//Параметр sort - сортировка по возрасту
    if(sort){//Если sort не нулевой, то проверяем на равенство возраста. 
        if(a->age != b->age){
            return a->age-b->age; //Выдаём результат
        }
        //Если всё таки равно, то сортируем по имени.
        for(int i = 0; a->name[i] || b->name[i]; i++){// a->name[i] || b->name[i] - пока хотя бы один из элементов не ноль - '\0'
            int diff = tolower((unsigned char)a->name[i]) - tolower((unsigned char)b->name[i]);//Кодировки разные коды символов имеют(включая отрицательные), поэтому приводим к беззнаковому char.
            if(diff){//Положит./отриц. значение - символы не равны
                return diff;
            }
        }
        return 0;
    }
    else{//Противоположный случай при sort = 0 -> Имя, возраст.
        for(int i = 0; a->name[i] || b->name[i]; i++){// a->name[i] || b->name[i] - пока хотя бы один из элементов не ноль - '\0'
            int diff = tolower((unsigned char)a->name[i]) - tolower((unsigned char)b->name[i]);//Кодировки разные коды символов имеют(включая отрицательные), поэтому приводим к беззнаковому char.
            if(diff){//Положит./отриц. значение - символы не равны
                return diff;
            }
        }
        return a->age - b->age;
    }
}

int main(int argc, char *argv[]){//МОЖНО ДОБАВИТЬ "AGE" и "REV"
    int sort = 0;//Переменная для сортировки
    int revers = 0;//Переменная для обратного порядка
    person *names = NULL;
    int k = 0;//Счётчик обхода
    int capacity = 0;
    char line[LINE_SIZE];

    //ДОП УСЛОВИЯ
    for(int i = 1; i<argc; i++){
        if(strcmp(argv[i], "age") == 0){
            sort = 1;
        }
        if(strcmp(argv[i], "rev") == 0){
            revers = 1;
        }
    }

    FILE *f_out = fopen("names_s.txt", "r");

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
            free(names);
            if(f_out){
                fclose(f_out);
            }
            return 1;
        }
        else{
            while(fgets(line, LINE_SIZE, f_in)){
                line[strcspn(line, "\n")] = '\0';
                person TEMP;
                if(sscanf(line, "%64s %d", TEMP.name, &TEMP.age) == 2){
                    int insert = 0;//Позиция вставки
                    while(insert<k && (revers ? comp(&names[insert], &TEMP, sort) >= 0 : comp(&names[insert], &TEMP, sort) <= 0)){//пока не переполнили и наше значение не больше нуля{если реверс, то не меньше}(нужно пройти те, которые меньше(больше для реверса) и равны, только потом вставлять)
                        insert++;
                    }

                    //Проверка дублей при добавлении с одинаковым аргументом несколько раз
                    int dupl = 0;//Переменная для дублей
                    if(insert > 0 && strcmp(names[insert-1].name, TEMP.name) == 0 && names[insert - 1].age == TEMP.age){//Можно comp либо strcmp - по барабану
                        dupl = 1;//перепрыгиваем на следующую итерацию при равенстве
                    }
                    if(insert < k && strcmp(names[insert].name, TEMP.name) == 0 && names[insert].age == TEMP.age){//Можно comp либо strcmp - по барабану
                        dupl = 1;//перепрыгиваем на следующую итерацию при равенстве
                    }
                    if(dupl){
                        continue;
                    }

                    if(k >= capacity){//Дополнение массива
                        capacity = capacity ? capacity * 2 : 4;//Тернарный оператор
                        person *tmp = realloc(names, capacity * sizeof(person));
                        if(!tmp){//Ошибка дополнения
                            perror("Error! Reallocation for main array");
                            free(names);
                            fclose(f_in);
                            if(f_out){
                                fclose(f_out);
                            }
                            return 1;
                        }
                        names = tmp;
                    }
                    for(int i = k; i>insert; i--){//Сдвиг элементов для вставки
                        names[i] = names[i - 1];
                    }
                    names[insert] = TEMP;
                    k++;
                }
            }
            fclose(f_in);
        }
    }

    if(f_out) fclose(f_out);

    FILE *f_res = fopen("names_s.txt", "w");
    if(!f_res){
        perror("Error! Opening file names_s.txt");
        free(names);
        return 1;
    }
    for(int i = 0; i<k; i++){
        fprintf(f_res, "%s %d\n", names[i].name, names[i].age);
    }
    fclose(f_res);
    //Вывод статистики
    if(k > 0){
        int min = names[0].age;
        int max = names[0].age;
        for(int i = 0; i < k; i++){
            if(names[i].age < min){
                min = names[i].age;
            }
            if(names[i].age > max){
                max = names[i].age;
            }
        }
        printf("Names count: %d\n", k);
        printf("Ages in range from %d to %d\n", min, max);
    }
    free(names);
    return 0;
}