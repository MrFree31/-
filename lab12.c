#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

void now(char *x, size_t size){
    time_t now = time(NULL);
    struct tm *now_f = localtime(&now);
    
    strftime(x, size, "%d-%m-%Y", now_f);   
}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    char input[20];
    printf("Введите формат(... now):");
    fgets(input, sizeof(input),stdin);

    int len = strlen(input);

    if(len>0 && input[len-1] == '\n'){
        input[len-1] = '\0';
    }

    if(strcmp(input, "now") == 0){
        char date[50];
        now(date, sizeof(date));
        printf("Настоящая дата: %s\n", date);
    }

    else{
        printf("Плохо всё.\n");
        return 1;
    }

    return 0;
}