#include <stdio.h>
#include <stdlib.h> //srand() rand()
#include <time.h> //time()
#include <string.h>

int main(){
    srand(time(NULL));//Задача генератора в зависимости от времени - NULL, то есть от 1970 года какого-то дня и месяца до настоящего момента



    int input, count_of_a;
    int right = 0;
    int wrong = 0;
    
    time_t start = time(NULL);

    printf("How many questions do you want?\n");
    printf("Enter: ");
    scanf("%d", &count_of_a);

    for(int i = 1; i <= count_of_a; i++){
        right = 0;
        int rand1 = rand() % 10 + 1;
        int rand2 = rand() % 10 + 1;
        int prod = rand1 * rand2;

        while(right == 0){
            printf("Example: %d * %d = ?\n", rand1, rand2);
            printf("Enter your answer: ");
            scanf("%d", &input);
            if(input != prod){
                printf("Your answer is wrong\n");
                wrong++;
            }
            else{
                printf("Your answer is right! Answer: %d\n", prod);
                right = 1;
            }
        }
        printf("\n");
    }
    time_t end = time(NULL);
    int answer_time = (int)(end - start);
    char *score = (char*)malloc(6*sizeof(char));
    if(wrong <= 5){
        strcpy(score,"Good");
    }
    else if(wrong > 5 && wrong <=10){
        strcpy(score,"Bad");
    }
    else if(wrong > 10){
        strcpy(score,"Awful");
    }

    printf("| Questions: %d | Time: %d | Mistakes: %d | Score: %s |\n", count_of_a, answer_time, wrong, score);

    char *name = (char*)malloc(20*sizeof(char));
    char *date_score = (char*)malloc(26*sizeof(char));

    printf("Enter your name: ");
    scanf("%19s", name);

    FILE *file = fopen("SCOREBOaRD.txt", "a");//a - append
    if(file != NULL){
        strcpy(date_score, ctime(&end));
        date_score[strlen(date_score) - 1] = '\0';
        fprintf(file, "| %-15s | %20s |\n", name, date_score);
        fprintf(file, "| Questions: %6d | Time: %6d | Mistakes: %6d | Score: %6s |\n", count_of_a, answer_time, wrong, score);
        fprintf(file, "\n");
    }
    else{
        printf("Error! Cant wright to SCOREBOaRD\n");
    }
    free(date_score);
    free(score);
    free(name);
    return 0;
}