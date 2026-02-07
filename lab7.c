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
//Тест вывода
for(int i=0;i<4;++i){
    printf("%dй кент: %s %s %d\n",i+1,p1[i].name,p1[i].surname,p1[i].birthyear);
}
return 0;
}