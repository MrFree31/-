#include <stdio.h>
#include <stdlib.h>//Дурацкий генератор rand
#include <time.h>//time для дурацкого генератора
#include <stdbool.h>// нормальный логический тип, чтобы не использовать int как флаг (хотя можно и без него)

//По классике 4 цифры в числе без повторов. 
int gen(){//Ничего не принимается
    int numbers[4];//4 значн.
    bool noRepeat; //Флаг повторки

    while(1){//Пока не найдем нужное число
        int num = rand() % 9000 + 1000;// (1*)
        noRepeat = true;

        int temp = num;
        for(int i = 3; i >= 0; i--){// С конца
            numbers[i] = temp % 10; // Классический подход для взятия опред. разрядов
            temp /= 10; //выбрасываем по цифре, так как int/int не даст float -> после запятой в помойку.
        }
        for(int i = 0; i < 3 && noRepeat; i++){
            for(int j = i + 1; j < 4; j++){
                if(numbers[i] == numbers[j]){
                    noRepeat = false;
                    break;//Цикл с j роняется через break и не проверяет все цифры, noRepeat = false. С i тоже роняется
                }
            }
        }
        if(noRepeat){//Проверка не выполняется и while начинает новую итерацию. Все счастливы.
            return num;
        }
    }
}
/*(1*) В идеале должны получаться остатки в промежутке от 0-8999, но нам нужно 4 цифры, поэтому +1000, но rand генерирует в промежутке между 0-RAND_MAX.
Обычно макрос RAND_MAX из stdlib.h равен 32767. 32767%9000 = 5767. Но в разных компиляторах разные пределы.
Исходя из этого рандомизация будет не равномерная, но это учебное, типо, задание*/

int main(){
    srand(time(NULL));//Инициализация генератора с кол-вом секунд с какого-то дня из 1970 года(Получается рандомный seed)

    int number = gen();

    int num_separation[4];//Опять разбиваем(В функции тоже самое делали, но ладно)
    int temp = number;
    for (int i = 3; i >= 0; i--) {
        num_separation[i] = temp % 10;
        temp /= 10;
    }

    int popitka = 1;
    while(1){
        int input;
        printf("Введите число(только 4 цифры в числе(Повторных не должно быть)): ");
        scanf("%d", &input);

        if(input < 1000||input > 9999){
            printf("Только 4 цифры в числе\n");
            continue;
        }

        int in_separation[4];//Разбивка ввода игрока
        temp = input;
        for(int i = 3; i >= 0; i--){
            in_separation[i] = temp % 10;
            temp /= 10;
        }

        int uniqueInput = 1;//Уникальность
        for(int i = 0;i < 3; i++){
            for(int j = i + 1; j < 4; j++){
                if(in_separation[i] == in_separation[j]){
                    uniqueInput = 0;
                    break;
                }
            }
            if(!uniqueInput){
                break;
            }
        }
        if(!uniqueInput){
            printf("Были введены цифры с повторами, так не надо делать\n");
            continue;
        }
        //Счётчик верных/не верных, наконец-то
        int b = 0;
        int c = 0;

        //Считаем верные/не верные
        for(int i = 0; i < 4; i++){
            if(in_separation[i] == num_separation[i]){//То же самое место
                b++;
            } 
            else{
                for(int j = 0; j < 4; j++){
                    if(in_separation[i] == num_separation[j]){//Произошёл сдвиг(по фазе у меня)
                        c++;
                        break;
                    }
                }
            }
        }
    }
    
    

    return 0;
}

