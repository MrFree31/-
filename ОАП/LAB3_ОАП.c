#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

struct tnode{
    int data;
    char *word;
    struct tnode *lchild;
    struct tnode *rchild;
};

int slov(FILE *fx, char *word, int max_len){
    int c;
    int i = 0;
    while((c = fgetc(fx))!= EOF && isalpha(c)==0){
        
    }
    if(c==EOF){
        return 0;
    }
    word[i]=tolower(c);
    i++;
    while((c=fgetc(fx))!=EOF && isalnum(c)>0){
        if(i<max_len-1){
            word[i] = tolower(c);
            i++;
        }
    }
    word[i]='\0';
    if(c != EOF){
        ungetc(c,fx);
    }
    return i;
}
    
int main(){
    SetConsoleOutputCP(CP_UTF8);
    int MAX_LEN = 50;
    char input[25];
    char word[MAX_LEN];
    int len;
    int ks = 0;
    struct tnode tree;

    printf("Введите имя файла: ");
    if(fgets(input,sizeof(input),stdin)==NULL){
        printf("Ошибка! Введена пустая строка");
        return 1;
    }

    input[strcspn(input,"\n")]='\0';
    FILE *fx;
    fx = fopen(input,"r");
    if(fx==NULL){
        printf("Ошибка! Файл не открыт");
        return 1;
    }
//Отладка slov
    while((len=slov(fx,word,MAX_LEN))>0){
        ks++;
        printf("Слово №%d - '%s', длинна = %d\n",ks,word,len);
    }

    if(len == 0 && feof(fx)){
        printf("Кол-во слов: %d\n",ks);
    }
    else{
        printf("Ошибка!");
    }
    fclose(fx);
    return 0;
}