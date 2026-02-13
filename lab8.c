#include <stdio.h>
#include <windows.h>
struct person{
    char name[20];
    char surname[20];
    char gender;
    int birthyear;
    float height;
};
int main(){
    SetConsoleOutputCP(CP_UTF8);
    FILE *f = fopen("lab8.txt","r");
    struct person *p = NULL;
    int c = 0;
    while(1){
        struct person temp;

        if (fscanf(f, "%19s %19s %c %d %f", 
        temp.name, temp.surname,&temp.gender,&temp.birthyear,&temp.height)!=5){
            break;
        }
        struct person *np = realloc(p,(c+1)*sizeof(struct person));
        if(np==NULL){
            printf("Ошибка: С выделением памяти напартачили!😡\n");
            free(p);
            return 1;
        }
        p = np;
        p[c]=temp;
        c+=1;
    }
    struct person pp[c];
    for(int i=0;i<c;i++){
        pp[i]=p[i];
    }
    fclose(f);
    char poryad;
    printf("По какому критерию сравнить челиков?(N,S,B,G,H): \n");
    scanf(" %c",&poryad);
    if(poryad=='N'){}
    else if(poryad=='S'){}
    else if(poryad=='B'){
        for(int i=0; i<c-1; i++){
            for(int j = i+1; j<c; j++){
                if(pp[i].birthyear>pp[j].birthyear){
                    //struct person temp = pp[i];
                    pp[i]=pp[j];
                    pp[j]=temp;
                }
            }
        }
    }
    else if(poryad=='G'){}
    else if(poryad=='H'){}
    else{printf("БУКВЫ ИЗ ПЕРЕЧНЯ ВВЕДИ💀");}
}