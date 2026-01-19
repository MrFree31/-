#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //кодировка русского в VSCode
int main()
{
    SetConsoleOutputCP(CP_UTF8); //кодировка русского в VSCode
    int c;
    printf("Введите порядок матрицы:\n");
    scanf("%d",&c);
    double mat[c][c];

    printf("Введите элементы матрицы через пробел:\n");
    for(int i=0;i<c;++i)
        for(int j=0;j<c;++j)
        scanf("%lf",&mat[i][j]);
        
    double sumg=0,sump=0;
    for(int i=0;i<c;++i)
        sumg+=mat[i][i],sump+=mat[i][c-1-i];


    double kvad[c][c];
    for(int i=0;i<c;++i){
        for(int j=0;j<c;++j){
            kvad[i][j] = 0;
            for(int k=0;k<c;++k)
                kvad[i][j]+=mat[i][k]*mat[k][j];
        }        
    }

    printf("Сумма главной = %.2lf, Сумма побочной = %.2lf\n",sumg,sump);
    printf("Квадрат матрицы:\n");
    for(int i=0;i<c;++i){
        for(int j=0;j<c;++j){
            printf(" %3.0lf",kvad[i][j]);
        }
    printf("\n");
    }
    return 0;
}   