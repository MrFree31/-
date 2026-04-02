#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int** createMatrix(int n){//Квадратная матрица, порядок n
    int** mat = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i<n; i++){
        mat[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j<n; j++){
            mat[i][j] = rand()%10;
        }   
    }
    return mat;
}

void clearMatrix(int** mat, int n){
    for(int i = 0; i<n ; i++){
        free(mat[i]);
    }
    free(mat);
}

void writeMatrix(FILE* f, int** mat, int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            fprintf(f,"%d",mat[i][j]);
            if(j<n-1) fprintf(f," ");
        }
        fprintf(f,"\n");
    }
}

int** readMatrix(FILE* f2, int n){
    int** mat = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i<n; i++){
        mat[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j<n; j++){
            fscanf(f2, "%d", &mat[i][j]);
        }
    }
    return mat;
}

int** prodMatrix(int** mat1, int** mat2, int n){
    int** mat3 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat3[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            mat3[i][j] = 0;
            for (int k = 0; k < n; k++) {
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return mat3;
}

int** sumMatrix(int** mat1, int** mat2, int n){
    int** mat3 = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i<n; i++){
        mat3[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j<n; j++){
            mat3[i][j] = mat1[i][j]+mat2[i][j];
        }
    }
    return mat3;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    clock_t start = clock();

    int n;
    printf("Введите порядок матрицы n: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Размер должен быть положительным.\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    int** A = createMatrix(n);
    int** B = createMatrix(n);

    FILE* f = fopen("input.txt", "w");
    if (!f) {
        printf("Ошибка открытия input.txt для записи\n");
        return 1;
    }
    writeMatrix(f, A, n);
    writeMatrix(f, B, n);
    fclose(f);

    clearMatrix(A, n);
    clearMatrix(B, n);

    f = fopen("input.txt", "r");
    if (!f) {
        printf("Ошибка открытия input.txt для чтения\n");
        return 1;
    }
    int** A_read = readMatrix(f, n);
    int** B_read = readMatrix(f, n);
    fclose(f);

    int** sum = sumMatrix(A_read, B_read, n);
    int** prod = prodMatrix(A_read, B_read, n);

    FILE* f_out = fopen("output.txt", "w");
    if (!f_out) {
        printf("Ошибка открытия output.txt\n");
        return 1;
    }
    fprintf(f_out, "Сумма матриц:\n");
    writeMatrix(f_out, sum, n);
    fprintf(f_out, "Произведение матриц:\n");
    writeMatrix(f_out, prod, n);
    fclose(f_out);

    clearMatrix(A_read, n);
    clearMatrix(B_read, n);
    clearMatrix(sum, n);
    clearMatrix(prod, n);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время работы программы: %f секунд\n", time_spent);

    return 0;
}