// Найти все "черные" области глифа, статистику глифов:
// размеры глифа и его битовая карта считываются из файла,
// Необходимо подсчитать количество "черных" пикселей,
// определить плотность, связность, диаметр, периметр глифа
//
// Найти похожие глифы путем сравнения глифов одинакового размера.
// Похожие глифы должны содержать не более 10% раличающихся пикселей.
// Составить списки похожих глифов
// Использовать инструмент "show" для контроля работы
// алгоритмов.
//
#include <stdio.h>
#include <stdlib.h>

#define ISBIT(n,x) (((01<<(n))&(x))?1:0)

void outbyte( char byte)
{          // Вывод байта в двоичном виде
  int i;
  for ( i=7; i>-1; i-- )
    putchar(ISBIT((i),byte)?'*':' ');
  fflush(stdout);
}

void outbytes( int n, char *byte)
{          // Вывод массива байтов в двоичном виде
  int i;
 for (i=0; i<n; i++)
   outbyte(byte[i]);
 putchar('\n');
}



typedef struct img { //  структура глифа - картинки
   int w; int h;     // ширина и высота в пикслелях
   int dx;           // расстояние до следующего глифа (если буква) ---> не используется в данной программе
   int count;   // черных пикселей всего ---> надо подсчитать и сравнить со значением из файла
   int id;      // иднтификатор - "номер" глифа
   int bytes;   // /количество байтов в битовой карте
   double density; // плотность черных пикселей        ---> проверить значение из файла
   int diam;       // диаметр в манхеттенской метрике  ---> нужно найти и заполнить
   int perim;      // периметр глифа                   ---> нужно найти и заполнить  
   int conn;       // связность                        ---> нужно найти и заполнить
   unsigned char *data;  //  битовая карта (неупакованная)
  } IMG;

int popcnt8 ( unsigned char i)
{   int count;
     count=0;
     while(i)
     { ++count;
       i=(i-1)&i; }
      return count;
}


int popcnt16 ( unsigned short int i)
{
return __builtin_popcount(i);   // ---> работает быстрее, чем закомментированный код
  //   i = i - ((i >> 1) & 0x5555);
  //   i = (i & 0x3333) + ((i >> 2) & 0x3333);
  //   return (((i + (i >> 4)) & 0x0F0F) * 0x0101) >> 8;
}

int popcnt64(unsigned long long w) {
//  return __builtin_popcountll(w);   // ---> работает медленнее !!! Почему - непонятно
    w -= (w >> 1) & 0x5555555555555555ULL;
    w = (w & 0x3333333333333333ULL) + ((w >> 2) & 0x3333333333333333ULL);
    w = (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    return (int)((w * 0x0101010101010101ULL) >> 56);
}

int popcnt32 ( unsigned int i)
{
//   return __builtin_popcountl(i);
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}


IMG *init_img(int id, int w, int h)
{             // создание пустого (чистого) глифа с заданными размерами
 IMG *t;
 t=(IMG *)malloc(sizeof(IMG)); 
  t->w=w; t->h=h; t->dx=0;
  t->count=0;
  t->id=id;
  t->bytes=(((w+7)/8)*h);
  t->data=(unsigned char *)calloc(t->bytes,1);
 return t;
}



IMG *load_img(int id, char *File)          //  считывание из каталога
{
  FILE *F;          // считывание из файла глифа с номером id
   IMG *I;
   I = (IMG *)malloc(sizeof(IMG));
    F = fopen(File,"rb");
  fread(&(I->w),sizeof(int),1,F);
  fread(&(I->h),sizeof(int),1,F);
  fread(&(I->dx),sizeof(int),1,F);
  fread(&(I->count),sizeof(int),1,F);
  fread(&(I->id),sizeof(int),1,F);
  fread(&(I->bytes),sizeof(int),1,F);
   I->data=(unsigned char *)calloc(I->bytes,1);
  fread(I->data,1,I->bytes,F);
  fclose(F);
  return I;
}
int xcomp (IMG **a, IMG **b)
{
   return	-(*a)->w+(*b)->w;
}
int ycomp (IMG **a, IMG **b)
{
   return	-(*a)->h+(*b)->h;
}

 IMG *G[50000];	
 int N;
    int ISPIX(int argc, int i, int j)
    {       if (i<0) return 0;
	    if (j<0) return 0;
            if (i>=G[argc]->w) return 0;
                    if (j>=G[argc]->h) return 0;
                       
      return 
       ISBIT((7-j%8), G[argc]->data[i*(G[argc]->bytes/G[argc]->h) +j/8 ]);
    }  
    
int get_pixel(IMG *glif, int i, int j){//Возьмём пиксель в пределах конкретного глифая, чтобы не разыскивать индекс в G для ISPIX 
	if(i<0||i>=glif->w||j<0||j>=glif->h){
		return 0;
	}
	int bytes_line = (glif->w+7)/8;
	int byte_id = i*bytes_line+j/8;
	unsigned char byte = glif->data[byte_id];
	int bit = 7 - (j%8);
	return (byte>>bit)&1;
}

void diametr(IMG *glif){
	int p_min = 10000, p_max = -10000, q_min = 10000, q_max = -10000;
	int flag = 0;
	for(int i = 0; i<glif->w; i++){
		for(int j = 0; j<glif->h; j++){
		
			if(get_pixel(glif,i,j)){
				flag = 1;
				int p = i+j;
				int q = i-j;
				if(p<p_min) = p_min = p;
				if(p>p_max) = p_max = p;
				if(q<q_min) = q_min = q;
				if(q>q_max) = q_max = q;				
			}	
		}
	}
	if(flag = 0){
		glif->diam = 0;
	}
	else{
		p = p_max - p_min;
		q = q_max - q_min;
		glif->diam = (p>q)?p:q;
	}
}

void perimetr(IMG *glif){//Возьмём за периметр шаги вокруг чёрныз пикселей 
	int P = 0;
	for(int i = 0; i<glif->w; i++){
		for(int j = 0; j<glif->h; j++){
			if(get_pixel(glif, i, j)){
				if(i==0 || get_pixel(glif, i-1, j)==0) P++;
				if(i==glif->w-1 || (glif, i+1, j)==0) P++;
				if(j==0 || get_pixel(glif, i, j-1)==0) P++;
				if(j==glif->h-1 || get_pixel(glif, i, j+1)==0) P++;
			}
		}
	}
	glif->perim = P;
}

int main( int argc, char *argv[])
{       long int c;
	int len;
	unsigned char *s;
	unsigned long long *t;
   N = argc-1;
   while (argc--)
      { 
         G[argc]=load_img(argc, argv[argc]);
	 printf("Loaded %s\n",argv[argc]);
     
	 c=0;  
	 t=(unsigned long long *)G[argc]->data;
	 s=(unsigned char *)G[argc]->data;

	 len=G[argc]->bytes;

   for (int i=0; i<len/8; i++)
       c+=popcnt64(t[i]);

   for (int i=(len/8)*8; i<len; i++)
       c+=popcnt8(s[i]);

     G[argc]->count=c;
     G[argc]->density = (double)G[argc]->count/(G[argc]->w*G[argc]->h);//Записываем плотность
      }
    printf("%d\n",N);
}
