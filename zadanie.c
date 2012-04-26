#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node* p;
  struct node *rank;
} t_node;

t_node *Z[100];

t_node* MakeSet(int k)
{
  // utworzenie zbioru reprezentujacego jednoelementowy zbior z kluczem k
  t_node *x;
  x = (t_node*) malloc(sizeof(t_node));

  x -> key = k;
  x -> p = x;
  return x;
}

t_node* FindSet(t_node* x)
{
  // zwraca reprezentanta zbioru do ktorego nalezy element (czyli wezel) x
  // Wersja bez kompresji
  if (x != x -> p) { return FindSet(x->p);}
  else {return x;}
}

t_node* Union(t_node* x,t_node* y)
{
  //zamienia zbiory o reprezentantach x,y w jeden zbior bedacy ich suma rozlaczn\
a
  //Wersja bez rangi
  y -> p = x;
}
void createSets(int ilosc) {
  int i;
  int t[1000];

  for (i = 0; i < ilosc; i++) {
    Z[i] = (t_node*) malloc(sizeof(t_node));
    scanf("%d",&t[i]);
    Z[i] = MakeSet(t[i]);
  }
}
void printSets(int ilosc) {
  int i;

  for (i = 0; i < ilosc; i++) {
    if (Z[i] == Z[i]->p ){
      t_node *tmp;
      tmp = (t_node*) malloc(sizeof(t_node));
      printf("\nZbior na pozycji: %d zostal wstawiony", i);
      tmp = Z[i]->p;
      printf("%d ",tmp->key);

    }
  }
}
int main()
{
  int t1,t2;
  int i,ilosc;
  int wyb=0;
  printf("\nZbiory rozlaczne\n");
  printf("1 - wstaw\n");
  printf("2 - polacz\n");
  printf("3 - drukuj\n");
  printf("4 - sprawdz\n");
  printf("5 - koniec\n");
  
  //  scanf("%d",&wyb);
  while(wyb!=5){
    printf("\nWybor: "); 
    scanf("%d",&wyb);
  switch(wyb)
    {
    case 1:  
      printf("Jednoelementowe zbiory\n");
      printf("Ile ma ich byc?\n");
      scanf("%d",&ilosc);
      createSets(ilosc);
      printSets(ilosc);
      break;
    case 2:
      printf("\nktore zbiory chcesz polaczyc\n");
      scanf("%d",&t1);
      scanf("%d",&t2);
      if(t1 > ilosc){
	return 0;
      }
      if(t2 > ilosc){
	return 0;
      }
      break;
    case 3:
      printSets(ilosc);
      break;
    case 4:
      printf("\n%d ",FindSet(Z[t1]));
      printf("%d ",FindSet(Z[t2]));
      Union(FindSet(Z[t1]), FindSet(Z[t2]));
      // printSets(ilosc);
      printf("\n%d ",FindSet(Z[t1]));
      printf("%d ",FindSet(Z[t2]));
      printSets(ilosc);
      break;
    case 5:
      return 0;
      break;
    }
  }
      return 0;
}


