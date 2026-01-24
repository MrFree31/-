#include <stdlib.h>
#include <windows.h> //Кодировка русского языка
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(){
SetConsoleOutputCP(CP_UTF8); //Кодировка русского языка
printf("1)Замена строчных\n");
printf("Введите строку(до 80 значений на английском)\n");
char str[81];
fgets(str,sizeof(str),stdin);
for(int i=0;i<strlen(str);++i)
    if(str[i]=='a'){
        str[i]='A';
    }

    else if(str[i]=='b'){
        str[i]='B';
    }
printf("===Вывод===");
for(int i=0;i<strlen(str);++i){
    printf("%c",str[i]);
    }

printf("2)Магический квадрат\n");
int p = 0;
print("Порядок матрицы\n");
scanf("%d", p);
int **mat = (int**)malloc(p * sizeof(int*));
for(int i=0;i<3;++i)
    mat[i] = (int*)malloc(p * sizeof(int));

printf("Введите переменные(9 шт)\n");
for(int i=0;i<3;++i){
    for(int j=0;j<3;++j){
    scanf("%d",&mat[i][j]);
    }
}

int sg = 0,sp = 0,sumsrav = 0;
for(int i=0; i<p; ++i){
    sumsrav += mat[0][i];
}

int true_false = 1;
for(int i=0;i<p;++i){
    int sumstr = 0;
    sg += mat[i][i], sp += mat[i][3-1-i];
    for(int j=0;j<p;++j){
        sumstr += mat[i][j];
    }
    if(sumstr != sumsrav){
        printf("Наша матрица - никакой не магический квадрат."); //доделать ответ
    }
}
if(sg==sp){
    printf("Наша матрица - Магический квадрат, Диагонали равны:%d",sg);
}

else{
printf("Наша матрица - никакой не магический квадрат. Главная диагональ - %d, побочная - %d",sg,sp);
}

return 0;
}