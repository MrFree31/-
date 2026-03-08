#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>
#include <windows.h>

void handler(int sig){
    const char* name;
    switch (sig)
    {
    case SIGABRT: name = "SIGABRT"; break;
    case SIGFPE: name = "SIGFPE"; break;
    case SIGILL: name = "SIGILL"; break;
    case SIGINT: name = "SIGINT"; break;
    case SIGSEGV: name = "SIGSEGV"; break;
    case SIGTERM: name = "SIGTERM"; break;
    
    default: name = "Неизвестен";
        break;
    }
    printf("Получен сигнал: %s\n", name);
}
int main(){
    SetConsoleOutputCP(CP_UTF8);
    signal(SIGABRT,handler);
    signal(SIGFPE,handler);
    signal(SIGILL,handler);
    signal(SIGINT,handler);
    signal(SIGSEGV,handler);        
    signal(SIGTERM,handler);

    int s = 0;
    const char *s_v[] = {"1 = sigabrt","2 = sigfpe",\
        "3 = sigill","4 = sigint","5 = sigsegv","6 = sigterm"};
    printf("Сигналы для обработки: \n");
    for(int i = 0; i<6; i++){
        printf("%s \n",s_v[i]);
    }
    
    while (1)
    {
        printf("Вызов сигнала: ");
        scanf("%d",&s);
        switch (s)
        {
        case 1: raise(SIGABRT); break;
        case 2: raise(SIGFPE); break;
        case 3: raise(SIGILL); break;
        case 4: raise(SIGINT); break;
        case 5: raise(SIGSEGV); break;
        case 6: raise(SIGTERM); break;
        
        default: printf("Не верный ввод\n");
            break;
        }
    }
    
    
    return 0;
}