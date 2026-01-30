#include "unitl5.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h> //Кодировка русского языка
int main(){
SetConsoleOutputCP(CP_UTF8);//Кодировка русского языка
char sim = 0; int p1 = 0;
printf("Введите порядок матрицы\n");
scanf("%d",&p1);
if(p1<1){
    printf("*Ошибка* Порядок матрицы не может быть меньше 1!\n");
    return 1;
}
else{
    double **mat1 = (double**)malloc(p1 * sizeof(double*));
    for(int i = 0; i<p1; ++i){
        mat1[i] = (double*)malloc(p1 * sizeof(double));
    }
    double **mat2 = (double**)malloc(p1 * sizeof(double*));
    for(int i = 0; i<p1; ++i){
        mat2[i] = (double*)malloc(p1 * sizeof(double));
        }

    printf("Введите переменные первой матрицы(%d шт через пробел)\n",p1*p1);
    for(int i = 0; i<p1; ++i){
        for(int j = 0;j<p1; ++j){
            scanf("%lf",&mat1[i][j]);
        }
    }

    printf("Введите переменные второй матрицы(%d шт через пробел)\n",p1*p1);
    for(int i = 0; i<p1; ++i){
        for(int j = 0;j<p1; ++j){
            scanf("%lf",&mat2[i][j]);
        }
    }
    
    printf("Первая матрица:\n");
    printf("=================\n");
    for(int i = 0;i<p1;++i){
        for(int j = 0;j<p1;++j){
            printf("%8.2lf",mat1[i][j]);
        }
        printf("\n");
    }
    printf("=================\n");
    printf("\n");
    
    printf("Вторая матрица:\n");
    printf("=================\n");
    for(int i=0;i<p1;++i){
        for(int j=0;j<p1;++j){
            printf("%8.2lf",mat2[i][j]);
        }
        printf("\n");
    }
    printf("=================\n");
        
    printf("Какое действи выполнить?(+,-,*)\n");
    getchar();
    scanf(" %c", &sim);
    if(sim != '+'&& sim != '-'&& sim != '*'){
        printf("*Ошибка* НУЖНЫ СИМВОЛЫ: + - *!\n");
        return 1;
    }
    else{
        double **mat_res = (double**)malloc(p1 * sizeof(double*));
        for(int i=0;i<p1;++i){
            mat_res[i] = (double*)malloc(p1 * sizeof(double));
        }
        sdp(sim,p1,mat1,mat2,mat_res);
        printf("Результат ( %c ):\n", sim);
        printf("=================\n");
        for(int i=0;i<p1;++i){
            for(int j=0;j<p1;++j){
                printf("%8.2lf",mat_res[i][j]);
            }
            printf("\n");
        }
        printf("=================\n");    
        for(int i = 0; i<p1; ++i){
            free(mat1[i]);
            free(mat2[i]);
            free(mat_res[i]);
        }
        free(mat1);
        free(mat2);
        free(mat_res);
    }
    }
    return 0;
}

