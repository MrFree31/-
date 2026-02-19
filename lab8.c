#include <stdio.h>
#include <windows.h>
#include <string.h>
struct person{
    char name[20];
    char surname[20];
    char gender;
    int birthyear;
    float height;
};

int srav_str(const char *a, const char *b){
    while (*a && (*a==*b)){
        *a++,*b++;
    }
    return *(unsigned char*)a-*(unsigned char*)b;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    FILE *f = fopen("lab8.txt", "r");
    if (f == NULL) {
        printf("Не удалось открыть файл lab8.txt\n");
        return 1;
    }

    struct person p[100];
    int c = 0;

    while (c < 100 && fscanf(f, "%19s %19s %d %c %f",
        p[c].name, p[c].surname, &p[c].birthyear, &p[c].gender, &p[c].height) == 5) {
        c+=1;
    }
    fclose(f);

    if (c == 0) {
        printf("Файл пустой\n");
        return 1;
    }

    printf("Входные данные: \n");
    for(int i = 0;i<c; i++){
        printf("%s %s %d %c %.2f\n",
        p[i].name, p[i].surname, p[i].birthyear, p[i].gender, p[i].height);
    }

   // struct person pp[c];
    //for(int i=0;i<c;i++){
    //    pp[i]=p[i];
    //}
    char op[20];
    printf("По каким критериям СОРТИРовать 🚽 челиков?(N ,S ,B ,G, H)): \n");
    scanf("%s",op);
    for(int i = 0; i<c-1;i++){
        for(int j=i+1; j<c; j++){
            int srav = 0;


            for(int k=0;op[k]!='\0'; k++){
                char s = op[k];
                if(s=='N'|| s=='n'){srav = srav_str(p[i].name, p[j].name);}
                else if(s=='S'||s=='s'){srav = srav_str(p[i].surname, p[j].surname);}
                else if(s=='B'||s=='b'){srav = (p[i].birthyear > p[j].birthyear) - (p[i].birthyear < p[j].birthyear);}                         
                else if(s=='G'||s=='g'){srav = (p[i].gender > p[j].gender) - (p[i].gender < p[j].gender);}
                else if(s=='H'||s=='h'){srav = (p[i].height > p[j].height) - (p[i].height < p[j].height);}
                else{printf("БУКВЫ ИЗ ПЕРЕЧНЯ ВВЕДИ💀 '%c' не катит\n",s);}
                
                if (srav !=0)
                break;
            }
            

                if (srav > 0) {
                    struct person temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }  
                  
        }
        
    
          printf("Упорядоченные данные: \n");
    for(int i = 0;i<c; i++){
        printf("%s %s %d %c %.2f\n",
        p[i].name, p[i].surname, p[i].birthyear, p[i].gender, p[i].height);
        }
        return 0;
    }
    


    // else if(op=='B' || op=='b'){
    //     for(int i=0; i<c-1; i++){
    //         for(int j = i+1; j<c; j++){
    //             if(pp[i].birthyear>pp[j].birthyear){
    //                 struct person temp = pp[i];
    //                 pp[i]=pp[j];
    //                 pp[j]=temp;
    //             }
    //         }
    //     }
    // }



    

  
