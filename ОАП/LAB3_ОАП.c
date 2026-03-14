#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

struct tnode{
    int count;
    char *w;
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
    
char *zam(const char *str){
	if(str == NULL) return NULL;
	char *new_str = (char*)malloc(strlen(str)+1);//Один дополнительный для нуля-терминатора
	if(new_str!=NULL){
		strcpy(new_str,str);
	}
	return new_str;
}

struct tnode *new_child(const char *word){
	struct tnode *kor = (struct tnode*)malloc(sizeof(struct tnode));
	if(kor == NULL){
		printf("Ошибка! Память новому узлу не выделилась (new_child)");
		return 1;
	}
	kor->w = zam(word);
	if(kor->w == NULL){
		printf("Ошибка! Память слову не выделилась (strcopy)");
	}
	kor->count = 1;
	kor->lchild=kor->rchild=1;
	return kor;
}

 struct tnode *vstavka(struct tnode *kor, const char *word){
	if(kor == NULL){
		return new_child(word);
	}
	int cmp = strcmp(word,kor->w);
	if(cmp < 0) kor->lchild = vstavka(kor->lchild, word);
	else if(cmp >0) kor->rchild = vstavka(kor->rchild, word);
	else kor->count++;
	
	return kor;
}

void tree_output(FILE *fo, const struct tnode *kor){
	if(kor != NULL){
		tree_output(fo, kor->lchild);
		fprintf(fo, "Слово %s встречаются %d раз",kor->w,kor->count);
		tree_output(fo, kor->rchild);
	}
}

int main(argc,argv){
    SetConsoleOutputCP(CP_UTF8);
    int MAX_LEN = 50;
    char input[25];
    char word[MAX_LEN];
    int len;
    int ks = 0;
    struct tnode tree;
printf("Введите имя файла: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    FILE *f1;
    f1=fopen(input,"r");
    if(f1 == NULL){
        printf("Ошибка! Файл %s не прочитан - ПРОПУСКАЕМ \n",input);
        return 1;
    }

    printf("Файл %s открыт\n", input);
    return 0;
}
//     while((len=slov(fx,word,MAX_LEN))>0){
//         ks++;
//         printf("Слово №%d - '%s', длинна = %d\n",ks,word,len);
//     }

//     if(len == 0 && feof(fx)){
//         printf("Кол-во слов: %d\n",ks);
//     }
//     else{
//         printf("Ошибка!");
//     }
//     fclose(fx);
//     return 0;
// }