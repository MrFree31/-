#include "unitl4.h"//реализация
#include <math.h>
double per(double a,double b, double c){
    double x = a+b+c; 
    return x;
}
double s(double p, double a, double b, double c){
    double pp = p/2;
    double x = sqrt(pp*(pp-a)*(pp-b)*(pp-c));
    return x;
}
