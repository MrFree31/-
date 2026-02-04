#include <stdio.h>
#include <windows.h>
int main(){
SetConsoleOutputCP(CP_UTF8);
CreateFile("ElderNamesl6.txt",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
FILE *f1 = fopen("namesl6.txt","r"); 
FILE *f2 = fopen("ElderNamesl6.txt","w");
char fio[50];
int g;
while(fscanf(f1,"%s %d",fio,&g)==2){
    if(g>1980){
        fprintf(f2,"%s\n",fio);
        } 
    }
fclose(f1);
fclose(f2);    
return 0;
}