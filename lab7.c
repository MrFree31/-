#include <stdio.h>
#include <windows.h>
struct person{
char name[20];
char surname[20];
int birthyear;};
int main(){
SetConsoleOutputCP(CP_UTF8);
struct person p1[4], p2[4];
for(int i=0;i<4;++i){
    printf("Введи имя %dго человека\n",i+1);
    scanf("%19s",p1[i].name);
    printf("Введи фамилию %dго человека\n",i+1);
    scanf("%19s",p1[i].surname);
    printf("Введи год рождения %dго человека\n",i+1);
    scanf("%d",&p1[i].birthyear);
}
for(int i=0; i<4; i++){
    p2[i]=p1[i];
}
for(int i=0; i<3; i++){
    for(int j = i+1; j<4; j++){
        if(p2[i].birthyear>p2[j].birthyear){
            struct person temp = p2[i];
            p2[i]=p2[j];
            p2[j]=temp;
        }
    }
}
//Вывод
for(int i=0;i<4;++i){
    printf("%dй кент из второго массива: %s %s %d\n",i+1,p2[i].name,p2[i].surname,p2[i].birthyear);
}
return 0;
}