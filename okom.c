/* Dekompresja */

#include <stdio.h>
#include <stdlib.h>

/* wezel drzewa */
typedef struct wezel
{
  char litera;             /* litera okreslonego wezla */
  unsigned long int bits; /* warotosc z kodowanie litery */
  char nbits;             /* calkowita warosc kodowania */
  struct wezel *lewy;            /* wskaznik do lewej galezi drzewa */
  struct wezel *prawy;             /* wskaznik do prawej galezi drzewa */
} typWezla;                /* wskaznik do galezi drzewa */


int main(int argc, char *argv[])
{
  typWezla *Drzewo;        /* Drzewo kodowane */
  long int Dlpliku;      /* dlugosc pliku */
  int nElementow;         /* elementy drzewa */
  unsigned long int bits; /* bity dla dekodowania */
  FILE *fe, *fs;          /* pliki wejsciowe wyjsciowe */

  typWezla *p, *q;       
  unsigned char a;
  int i, j;

  if(argc < 3)
    {
      printf("Plik:\n%s <plik_wejsciowy> <plik_wyjsciowy>\n", argv[0]);
      return 1;
    }

  /* tworzenie drzewa z infomacjami z tabeli */
  Drzewo = (typWezla *)malloc(sizeof(typWezla)); /* nowy wezel */
  Drzewo->litera = 0;
  Drzewo->prawy = Drzewo->lewy = NULL;
  fe = fopen(argv[1], "rb");
  fread(&Dlpliku, sizeof(long int), 1, fe); /* przeczytaj liczbe znakow */
  fread(&nElementow, sizeof(int), 1, fe); /* przeczytaj ilosc elementow */
  for(i = 0; i < nElementow; i++) /* przeczytaj wszystie elementy */
    {
      p = (typWezla *)malloc(sizeof(typWezla)); /* nowy wezel */
      fread(&p->litera, sizeof(char), 1, fe); /* przeczytaj znak */
      fread(&p->bits, sizeof(unsigned long int), 1, fe); /* przeczytaj kod */
      fread(&p->nbits, sizeof(char), 1, fe); /* przeczytaj dlugosc */
      p->lewy = p->prawy = NULL;
      /* wstaw wezel */
      j = 1 << (p->nbits-1);
      q = Drzewo;
     
      while(j > 1)
	{
	  if((p->bits & j) !=0) 
            if(q->prawy!=0) q = q->prawy;   /* jesli prawy wezel isnieje */
            else                     /* jesli nie utworz go */
	      {
		q->prawy = (typWezla *)malloc(sizeof(typWezla)); 
		q = q->prawy;
		q->litera = 0;
		q->prawy = q->lewy = NULL;
	      }
	  else /* jest lewy */
            if(q->lewy != 0) q = q->lewy; /* jesli lewy wezel istnieje */
            else                     /* jesli nie utworz go */
	      {
		q->lewy = (typWezla *)malloc(sizeof(typWezla)); 
		q = q->lewy;
		q->litera = 0;
		q->prawy = q->lewy = NULL;
	      }
	  j >>= 1;  /* Nastepny bit */
	}
      /* Ostatni bit */
      if((p->bits & 1) !=0) /* jest prawy*/
	{	q->prawy = p;/*printf("1 %c",p->litera);*/}
      else            /* jest lewy */
	{q->lewy = p;/* printf("0 %c ",p->litera);*/}
    }
 
  bits = 0;
  fs = fopen(argv[2], "w");
  /* przeczytaj pierwsze 4 bajty */
  fread(&a, sizeof(char), 1, fe);
  /*printf("%d",a);*/
  bits |= a;
  bits <<= 8;
  fread(&a, sizeof(char), 1, fe);
  /*printf("%d",a);*/
  bits |= a;
  bits <<= 8;
  fread(&a, sizeof(char), 1, fe);
  /*printf("%d",a);*/
  bits |= a;
  bits <<= 8;
  fread(&a, sizeof(char), 1, fe);
  /*printf("%d",a);*/
  bits |= a;
  j = 0; 
  q = Drzewo;
  /* Petla */
  do {
    if((bits & 0x80000000) !=0) q = q->prawy; else q = q->lewy; 
    bits <<= 1;           /* Nastepny bit */
    j++;
    if(8 == j)            /* Co 8 bitow */
      {
      	i = fread(&a, sizeof(char), 1, fe); /* odczytac bajt z pliku */
	bits |= a;                    
	j = 0;                        
      }                                
    if(q->prawy==0 && q->lewy==0)          /* jesli wezel nie jest pietrowy */
      {
	putc(q->litera, fs);           
	Dlpliku--;                   
	q=Drzewo;                      /* wracamy do korzenia drzewa */
      }
  } while(Dlpliku);                  /* do konca pliku */
  

  fclose(fs);                         
  fclose(fe);

 
  return 0;
}

