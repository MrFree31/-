#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct poly{//Структура полигон
    int N; //Кол-во вершин
    double *x; //Массивы координат
    double *y;
}poly;

/*
typedef struct point{//Структура точки
    double x, y;
}point;
*/

poly *createPoly(int n){
    if(n<3){
        printf("For poly count of vertices must be greater then 2!\n");
        return NULL;
    }
    poly *p = (poly*)malloc(sizeof(poly));
    if(!p){
        perror("Error! Cant create poly struct");
        return NULL;
    }
    p->N = n;
    p->x = (double*)malloc(n*sizeof(double));
    p->y = (double*)malloc(n*sizeof(double));
    if(!p->x || !p->y){
        perror("Error! Cant create coordinate arrays");
        free(p->x);
        free(p->y);
        free(p);
        return NULL;
    }
    return p;
}

void freePoly(poly *p){
    if(p){
        free(p->x);
        free(p->y);
        free(p);
    }

}

double poly_d(poly *p){//Диаметр многоугольника(Пример так называемого алгоритмов BruteForce-ного типа)
    if(p == NULL || p->N < 3){//Если он пустой или не многоугольник (минимальный многоугольник - треугольник)
        return 0.0;//Дабл - возвращаем дабл
    }

    double D = 0.0;//итоговый диаметр(Для сравнения важно дать значение)
    int n = p->N;//Кол-во точек в многоугольнике для цикла

    for(int i = 0; i<n; i++){
        for(int j = i + 1; j<n; j++){
            double dx = p->x[i]-p->x[j];//Дельта X
            double dy = p->y[i]-p->y[j];//Дельта y
            double sd = dx*dx + dy*dy;//sqrt() - ресурсоёмкая функция, поэтому сраниваем квадраты длины, вместо вычисления sqrt() каждый раз.
            if(sd > D){
                D = sd;
            }
        }
    }
    return sqrt(D);
}

double poly_area(poly *p){//Формула площади произвольного многоугольника Гаусса(Шнуровка). Асимптотическая оценка: O(n). Пример так называемых "Итеративных (прямых) алгоритмов"
    if(!p || p->N < 3){
        return 0.0;
    }

    int n = p->N;
    double area = 0.0;//Формула Гаусса требует суммирования и вычитания, поэтому сразу задаём нулевое значение
    for(int i = 0; i<n; i++){
        int j = (i + 1) % n; //Закольцовываем обход(Если n = 4, i = 3, j = (3 + 1) % 4 = 0)
        area += p->x[i]*p->y[j];//Формула: 1/2(fabs(sum_i=0^n-1=(x[i]*y[i+1]-x[i+1]*y[i])))
        area -= p->x[j]*p->y[i];
    }
    return 0.5*fabs(area);
}

double poly_perimetr(poly *p){
    if(!p || p->N < 3){
        return 0.0;
    }

    int n = p->N;
    double perim = 0.0;
    for(int i = 0; i<n; i++){
        int j = (i + 1) % n;
        double dx = p->x[i] - p->x[j];
        double dy = p->y[i] - p->y[j];
        perim += sqrt(dx*dx + dy*dy);
    }
    return perim;
}

int main(){
    int n;
    bool input = false;
    while(!input){
        printf("Enter count of vertices in poly: ");
        scanf("%d", &n);
        if(n < 3){
            printf("Invalid input\n");
            continue;
        }
        else{
            input = true;
        }
    }

    poly *polygone = createPoly(n);

    printf("Enter coordinate values (x,y) ==TRAVERSAL ORDER==: \n"); // Если будут введены данные без порядка всё пойдёт прахом
    for(int i = 0; i<n; i++){
        printf("Vertex number %d: ", i + 1);
        if(scanf("%lf %lf", &polygone->x[i], &polygone->y[i]) != 2){//Сразу читаем данные и проверяем кол-во элементов в входной строке
            printf("Error! There is pair of coordinates\n");
            freePoly(polygone);
            return 1;
        }
    }
    double perimetr = poly_perimetr(polygone);
    double area = poly_area(polygone);
    double D = poly_d(polygone);

    printf("Polygone has %d vertices, area = %.2lf, perimetr = %.2lf, diametr = %.2lf\n", n, area, perimetr, D);
    freePoly(polygone);
    return 0;
}