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
    struct person p[100];
    int i = 0;
    while(fscanf(f, "%19s %19s %s %d %f", 
        p[i].name, p[i].surname,p[i].gender,p[i].birthyear,p[i].height)==5){
            i+=1;
            if(i>=100) break;
    }
    fclose(f);
    char poryad;
    printf("По какому критерию сравнить челиков?(Введи первую букву:И,Ф,Д,П,Р): \n");
    scanf('%s',&poryad);
    if(poryad=='И'){}
    else if(poryad=='Ф'){}
    else if(poryad=='Д'){}
    else if(poryad=='П'){}
    else if(poryad=='Р'){}
    else{printf("БУКВЫ ИЗ ПЕРЕЧНЯ ВВЕДИ💀");}
}