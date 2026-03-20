#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    long l;
    int k=0;
    double d;
    long long ll;
    printf("Введите long: ");
    scanf("%ld",&l);
    printf("Введите double: ");
    scanf("%lf",&d);
    unsigned long ul = (unsigned long)l;
    while(ul){
        ul &= (ul-1);
        k++;
    }
    printf("Long = %ld, единиц в двоичном представлении: %d шт.\n",l,k);
    k = 0;
    memcpy(&ll,&d,sizeof(double));
    while(ll){
        ll &= (ll-1);
        k++;
    }
    printf("Double = %.2lf, единиц в двоичном представлении: %d шт.\n",d,k);
}