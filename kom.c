/* Kompresja */

#include <stdio.h>
#include <stdlib.h>


typedef struct wezel
{
  char litera;      /* litery */
  int czest;  /* czestotliwos wystapienia */
  struct wezel *nast;      /* wskaznik nastepnego wezla  */
  struct wezel *lewy;     /* wskaznik lewj galezi */
  struct wezel *prawy;      /* wskaznik do prawej galezi */
} typWezla;         

/* wezel budujacy liste kodow dla tabeli */
typedef struct tablica
{
  char litera;      /* litery */
  unsigned long int bits; /* wartosc kodowanej litery */
  char nbits; /*pietro od najmniejszego w po korzeniu */      
  struct tablica *nast;     /* nastepny element w tabeli */
} typTablicy;       

typTablicy *Tablica;

void CreateTable(char c, int l, int v)
{
  typTablicy *t, *p, *a;
  /*  printf("v %d l %d\n",l,v);*/
  t = (typTablicy *)malloc(sizeof(typTablicy)); /* tworzy element tabeli */
  t->litera = c;                               
  t->bits = v;
  t->nbits = l;
  /*printf("t->bits %u t->nbits %u t->litera %c\n",t->bits,t->nbits,t->litera);*/

      if(Tablica==NULL)         /* jesli tablica jest NULL */
     {
      Tablica = t;
      Tablica->nast = NULL;
    }
  else
  {
      /* szukaj znakow na liscie wg czestoliwosci */
     p = Tablica;
      a = NULL;
      
      while(p!=0 && p->litera < t->litera)
	{
	a = p;      /* Zapisz bierzacy element do wstawienia */
       p = p->nast; /* przejdz do nastepnego */
    	}
      /* wstaw element */
      t->nast = p;
      if(a!=0) a->nast = t;  
      else Tablica = t;    
    }
   
}
/* Funkcja rekursywna do utowrzenia tabeli */
void StworzTab(typWezla *n, int l, int v)
{
  /*  printf("rek l %d v %d\n",l,v); */
   if(n->prawy!=0) StworzTab( n->prawy, l+1, (v<<1)|1);
   if(n->lewy!=0) StworzTab( n->lewy, l+1, v<<1);
  if(n->prawy==0 && n->lewy==0) CreateTable(n->litera, l, v);
}



/* Wyszukiwanie za pomoca znaku w tabeli  */
typTablicy *ZnajdzChar(typTablicy *Tablica, char c)
{
  typTablicy *t;

  t = Tablica;
  while(t!=0 && t->litera != c) t = t->nast;
  return t;
}

int main(int argc, char *argv[])
{
  typWezla *Lista;       
  typWezla *Drzewo;      
  FILE *fe, *fs;         
  char c;                
  typWezla *p;
  typTablicy *t;
  int nElementow;        /* calkowita liczba elementow w tabicy */
  long int Dlpliku = 0; /* dlugosc oryginalnego pliku */
  unsigned long int dWORD; /* znaki do kodowania */
  int nBits;               /* calkowita liczba bitow */

  if(argc < 3)
    {
      printf("Pliki:\n%s <plik_wejsciowy> <plik_wyjsciowy>\n", argv[0]);
      return 1;
    }

  Lista = NULL;
  fe = fopen(argv[1], "r");
  while((c = fgetc(fe)) != EOF)
    {
      Dlpliku++;       /* Dlugosc pliku */
     
      typWezla *r, *a, *q;

      if(Lista==0)  /* jesli lista jest pusta */
	{
	  /* wstaw pierwszy znak */
	  Lista = (typWezla *)malloc(sizeof(typWezla)); /* nowy wezel */
	  Lista->litera = c;                             /* dla znaku */
	  Lista->czest = 1;                        
	  Lista->nast = Lista->lewy = Lista->prawy = NULL;
	 
	}
      else
	{
	  r = Lista;
	  a=NULL;
	   while(r && r->litera<c)
	       {
	            a=r;
	      r=r->nast;
	       }	  
	  /* jesli znak jest powtorzony */
	  if(r!=0 && r->litera == c) r->czest++;
           /* zwieksz czest */
	  else
	    /* wstawiamy kolejne znaki do wezla*/
	    {
	      q = (typWezla *)malloc(sizeof(typWezla));
	      q->litera = c;
	      q->czest = 1;
	      q->lewy = q->prawy = NULL;
	      q->nast = r;
	       if(a) a->nast = q;        
	    		else Lista = q;
     	    }
	}

    }
  fclose(fe);
  /*    o = Lista;
  while(o!=0)
    {
      printf("lit %c czest %d\n",o->litera,o->czest);
      o = o->nast;
    }
  */

  /* Sortowanie listy */
  
  typWezla *Lista2, *a;
  Lista2 = Lista;
  Lista = NULL;
  while(Lista2)
    {
      a = Lista2;              
      Lista2 = a->nast;
      
      typWezla *p, *now;

      if(Lista==0) 
	{
	  Lista = a;
	  Lista->nast = NULL;
	}
      else
	{      
	  p = Lista;
	  now = NULL;
	  while(p!=0 && p->czest < a->czest)
	    {
	      /*  printf(" p->czest %d  a->czest %d\n",p->czest,a->czest);*/
	      now = p;      /* zapisz bierzacy element do wstawienia*/
	      p = p->nast; 
	    }
	  /* wstaw element */
	  a->nast = p;
	  if(now!=0) now->nast = a;   
	  else Lista = a;    
	}
    }
  /*po sortowaniu*/
  /*  o = Lista;
  while(o!=0)
    {
      printf("lit %c czest %d\n",o->litera,o->czest);
      o = o->nast;
    }
  */

  /* Tworzenia drzewa */
  Drzewo = Lista;
  while(Drzewo && Drzewo->nast) /* jesli istnieja co najmniej 2 pozycje na liscie spacja i znak*/
    {
     
      p = (typWezla *)malloc(sizeof(typWezla)); /* nowe drzewo */
      p->litera = 0;                             
      p->prawy = Drzewo;                           
      Drzewo = Drzewo->nast;                       /* nastepny wezel */
      p->lewy = Drzewo;                          
      Drzewo = Drzewo->nast;                       /* nastepny wezel */
      p->czest = p->prawy->czest + 
	p->lewy->czest;      /* suma czestotliwosci */ 
      /*   printf("lit %c czest %d\n",p->litera,p->czest); */      
      typWezla *nowe, *a;

      if(Drzewo==0) 
	{
	  Drzewo = p;
	  Drzewo->nast = NULL;
	}
      else
	{
	  /* szukaj znaku na liscie wg czestoliwosci */
	  nowe = Drzewo;
	  a = NULL;
	  while(nowe!=0 && nowe->czest < p->czest)
	    {
	      a = nowe;      /* zapisz bierzacy element do wstawienia */
	      nowe = nowe->nast; /* przechodzimy do nastepnego */
	    }
	  /* wstaw element */
	  p->nast = nowe;
	  if(a!=0) a->nast = p;  
	  else Drzewo = p;    
	}
    }                                            /* orden de czest */

  
  /* Budowanie binarnych tabieli kodow */
  Tablica = NULL;
  StworzTab(Drzewo, 0, 0);

  /* Tworzenie skopresowanego pliku */
  fs = fopen(argv[2], "wb");
  /* napisz dlugosc pliku */
  fwrite(&Dlpliku, sizeof(long int), 1, fs);
  nElementow = 0;
  t = Tablica;
  while(t!=0)
    {
      nElementow++; /* ilosc znakow nie powtarzajacych sie */
      t = t->nast;
    }
  
  fwrite(&nElementow, sizeof(int), 1, fs);
  
  /* t = Tablica;
  while(t!=0)
    {
      printf("lit %c bit %ld nbit %d\n",t->litera,t->bits,t->nbits);
      t = t->nast;
      }*/
  t = Tablica;
  while(t!=0)
    {
      fwrite(&t->litera, sizeof(char), 1, fs);
      fwrite(&t->bits, sizeof(unsigned long int), 1, fs);
      fwrite(&t->nbits, sizeof(char), 1, fs);
      t = t->nast;
    }

  /* Kodowanie z pliku wejsciowego */
  fe = fopen(argv[1], "r");
  dWORD = 0; /* warosc poczatkowa */
  nBits = 0; 
  while((c = fgetc(fe)) != EOF)
    {
           
      /* Znajdz nie powtarzajace sie znaki: */
      t = ZnajdzChar(Tablica, c);
      /* printf("po char nb %d b %d %c",t->nbits,t->bits,t->litera);*/
      while(nBits + t->nbits > 32)
	{
	  c = dWORD >> (nBits-8);           /* usun 8 najbardziej znaczacych bitow  */	   
	  fwrite(&c, sizeof(char), 1, fs);  /* i zapisz je do pliku */
	  nBits -= 8;                       /* jest wiecej miejsca dla 8 bitow */
	}
      /* printf("1 dword %d t->nbits %d ",dWORD,t->nbits);*/     
      dWORD <<= t->nbits; /* zrob miejsce dla nowego znaku */
      /*printf("2 dword %d ",dWORD);*/
       dWORD |= t->bits;
      /*printf("3 dword %d nBit %d\n",dWORD,nBits);*/   
      nBits += t->nbits;  /* aktualizacja liczby bitow */
    }
  /*printf("%d dWORD %d\n",nBits,dWORD);*/
  /* usun 4 pozostale bajty*/
  while(nBits>0)
    {
      /*  printf("%d \n",nBits);*/
      if(nBits>=8) c = dWORD >> (nBits-8);
      else c = dWORD << (8-nBits);
      /*printf("%d \n",c);*/
      fwrite(&c, sizeof(char), 1, fs);
      nBits -= 8;
    }

  fclose(fe);  /* zamknij plik */
  fclose(fs);
  return 0;
}


