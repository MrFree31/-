#include <stdio.h>
#include <windows.h>
struct person{
char name[20];
char surname[20];
int birthyear;};
int main(){
SetConsoleOutputCP(CP_UTF8);
struct person p1[4], p2[4];
char z;
printf("Данные из файла или ручной ввод F/H?: ");
scanf(" %c",&z);
if(z == 'F' || z == 'f'){
     FILE *f = fopen("lab7.txt", "r");
        if (f == NULL) {
            printf("Ошибка: с файлом беда (файл lab7.txt)\n");
            return 1;
        }
        for (int i = 0; i < 4; i++) {
            fscanf(f, "%19s %19s %d", p1[i].name, p1[i].surname, &p1[i].birthyear);
        }
}
else if(z == 'H' || z == 'h'){
    for(int i=0;i<4;++i){
        printf("Введи имя %dго человека\n",i+1);
        scanf("%19s",p1[i].name);
        printf("Введи фамилию %dго человека\n",i+1);
        scanf("%19s",p1[i].surname);
        printf("Введи год рождения %dго человека\n",i+1);
        scanf("%d",&p1[i].birthyear);
    }
}
else{
    printf("Ошибка: Либо Ф, либо Р!");
    return 1;
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
    printf("%dй кент по возрасту: %s %s %d\n",i+1,p2[i].name,p2[i].surname,p2[i].birthyear);
}
return 0;
}