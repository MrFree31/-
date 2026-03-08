#include <stdio.h>
#include <windows.h> //Кодировка русского языка
int main(){
SetConsoleOutputCP(CP_UTF8);
FILE *f1 = fopen("namesl6.txt","r"); 
FILE *f2 = fopen("ElderNamesl6.txt","w");
char f[50],i[50],o[50];
int g;
while(fscanf(f1,"%s %s %s %d",f,i,o,&g)==4){
    if(g>1980){
        fprintf(f2,"%s %s %s %d\n",f,i,o,g);
        } 
    }
fclose(f1);
fclose(f2);    
printf("Чекай новый файл в папке😠(ElderNamesl6.txt)\n");
printf("А почему elder, если по логике Younger?😵‍💫");
return 0;
}