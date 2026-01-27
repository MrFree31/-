#include "unitl5.h"
#include <stdio.h>
int sdp(ao,m1,m2,n1,n2){
    //Сумма
    if(ao=='+'){
        if(m1!=m2||n1!=n2){
        printf("*Ошибка* Размерность матриц не совпадает!\n");
        return 1;
        }
        else{
            for(int i=0;i<m1;++i){
                for(int j=0;j<n1;++j){
                    mat_result[i][j]=mat1[i][j]+mat2[i][j];

                }
        
            }
        }
    }
    //Разница
    else if(ao=='-'){ 
    if(m1!=m2||n1!=n2){printf("*Ошибка* Размерность матриц не совпадает!\n"); return 1;}
    else{
        for(int i=0;i<m1;++i){
            for(int j=0;j<n1;++j){
                mat_result[i][j]=mat1[i][j]-mat2[i][j];

                }
            
            }
        }
    }
    //Произведение
    else if(ao=='*'){
        if(n1==m2){

        }
        else{printf("*Ошибка* Размеры матрицы не подходят для произведения!"); return 1;}

    }
    //Другой символ
    else{printf("*Ошибка* Не в этот раз, дружок(!!!Только сумма, разница, произведение!!!)"); return 1;}
}