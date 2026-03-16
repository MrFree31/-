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

int slov(FILE *fx, char *word, int max_len){//Чтение слов
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
    
char *zam(const char *str){//Выделение памяти под новое слово
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
		printf("Ошибка! Память новому узлу не выделилась (new_child)\n");
		return NULL;//функция возвращает указатель => возвращаем NULL, а не 1, как было
	}
	kor->w = zam(word);
	if(kor->w == NULL){
		printf("Ошибка! Память слову не выделилась (strcopy\n)");
        free(kor);
        return NULL;//функция возвращает указатель => возвращаем NULL, а не 1, как было
	}
	kor->count = 1;
	kor->lchild=kor->rchild=NULL;
	return kor;
}

 struct tnode *vstavka(struct tnode *kor, const char *word){//Добавление/счёт слов
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
		fprintf(fo, "Слово %s встречаются %d раз\n",kor->w,kor->count);
		tree_output(fo, kor->rchild);
	}
}

void srub(struct tnode *kor){//Освобождение памяти от дерева(рубим, типо)
    if(kor != NULL){
        srub(kor->lchild);
        srub(kor->rchild);
        free(kor->w);
        free(kor);
    }
}

struct tnode *search(struct tnode *kor,const char *input, int len){
    if(kor == NULL){
        return NULL;
    }
    struct tnode *lbranch = search(kor->lchild,input, len);
    if(lbranch != NULL){
        return lbranch;
    }
    if(strncmp(kor->w,input,len) == 0){
        return kor;
    }
    return search(kor->rchild,input,len);
}

int main(int argc, char *argv[]){
    SetConsoleOutputCP(CP_UTF8);
    int MAX_LEN = 64;
    //char input[25];
    char word[MAX_LEN];
    int len;
    int ks = 0;
    struct tnode *tree=NULL;

    FILE *fo = fopen("LAB3_Output.txt", "w");
    if(fo == NULL){//Проверка до обработки
        printf("Ошибка! Файл не удалось создать\n");
        srub(tree);
        return 1;
    }

    for(int i = 1; i < argc; i++){//Перебор файлов из аргумента
        FILE *fp = fopen(argv[i],"r");
        if(fp == NULL){
            printf("Ошибка! Файл %s не открылся\n",argv[i]);
            continue;
        }
        while(slov(fp, word, sizeof(word))>0){
            tree = vstavka(tree, word);
        }
        fclose(fp);
    }

    tree_output(fo, tree);
    fclose(fo);
    printf("Словарь в файле 'LAB3_Output.txt'\n");
    
    printf("Введите буквы для поиска (до 5 шт): ");
    char input[6];//Шестой - "\0"

    if (scanf("%5s", input) == 1) {
        int len = strlen(input);
        if(len==0){
            printf("Ошибка! Ввод пуст\n");
            return 1;
        }
        else{

        
           
            struct tnode *find = search(tree, input, len);
            if (find != NULL){
                printf("Найдено слово: %s, встречается %d раз)\n", find->w, find->count);
            }

            else{
                printf("По вводу: %s слов нет\n", input);
                
            }
        
        }
    }

    srub(tree);
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