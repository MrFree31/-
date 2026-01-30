#include "unitl5.h"//реализация
#include <stdio.h>
double sdp(char ao, int n, double** m1, double** m2, double** mr){
    //Сумма
    if(ao =='+'){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                mr[i][j] = m1[i][j] + m2[i][j];
            }  
        }
        return 0;
    }
    //Разница
    else if(ao=='-'){ 
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                mr[i][j] = m1[i][j] - m2[i][j];

            }
        }
        return 0;
    }
    //Произведение
    else if(ao =='*'){
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                mr[i][j] = 0;
                for(int k = 0; k < n; ++k) {
                    mr[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
        return 0;
    }
    //Другой символ
    else {printf("*Ошибка* Не в этот раз, дружок(!!!Только сумма, разница, произведение!!!)"); return 1;}
}    