#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main(){
	SetConsoleOutputCP(CP_UTF8);//Кодировочка для VScode(В консоли обычной тоже работает, вроде, да)
	int n,k=0, p = 2;
	printf("Введите предел значений n: ");
	scanf("%d", &n);

	if(n < 2){
		printf("Простых чисел нет в пределе(Минимумальный предел - 2)\n");
		return 1;
	}
	
	int *P = (int*)malloc((n+1)*sizeof(int));
	if(P == NULL) {
		printf("Ошибка! Памяти нет, автор кода...");
		return 1;
	}
	for(int i = 0; i<n+1; i++){ //Заполняем массив числами в пределе n
		P[i]=i;
	}
	
	while (p*p<n+1){ //Удаление кратных
		if(P[p] != 0){
			for(int i = p*p; i<n+1; i += p){
				P[i] = 0;
				
			}
		}
		p++;
		while(p<n+1 && P[p] == 0){
			p++;
		}
	}
	printf("Числа: \n");
	for(int i=2; i<n+1; i++){
		if(P[i]!=0){
			printf("%d ", P[i]);
			k++;
		}
	}
	
	printf("\n");
	printf("Кол-во простых: %d",k);
	free(P);
	return 0;
}