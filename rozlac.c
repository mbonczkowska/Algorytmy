#include <stdio.h>
#include <stdlib.h>

#define NIL NULL
typedef struct node {
  int key;
  struct node* p;
  struct node *rank;
} t_node;

t_node *Z[100];
t_node *Set1;
t_node* MakeSet(int k)
{
 /* utworzenie zbioru reprezentujacego jednoelementowy zbior z kluczem k */
t_node *x;
x = (t_node*) malloc(sizeof(t_node));

 x -> key = k;
 x -> p = x;

 return x;
}

t_node* FindSet(t_node* x)
{
  /* zwraca reprezentanta zbioru do ktorego nalezy element (czyli wezel) x*/
  /* Wersja bez kompresji*/
  if (x != x -> p) { FindSet(x->p);}
  else {return x;}
}

void Union(t_node* x,t_node* y)
{

 /*zamienia zbiory o reprezentantach x,y w jeden zbior bedacy ich suma rozlaczna*/
 /*Wersja bez rangi*/
    y -> p = x;
}

void createSets(int ilosc) {
  int i;
  int t[1000];

  for (i = 0; i < ilosc; i++) {
      scanf("%d",&t[i]);
    Z[i] = MakeSet(t[i]);
  }
}
void printSets(int ilosc) {
  int i,u;
    t_node *tmp;
      for (i = 0; i < ilosc; i++) {
       tmp = FindSet(Z[i]);
         if (Z[i] == Z[i]->p ){
           printf("\n%d) %d",i,tmp->key);
     }
         else{
           printf(" %d) %d",i,tmp->key);

       }
   }
}
int main()
{
  int t1,t2;
  int ilosc,k=0;
  while(k!=4){
    printf("\nDodaj - 1\nDrukuj - 2\nPolacz - 3\nWyjdz - 4\n");
    scanf("%d",&k);
  switch(k)
{
  case 1:
         printf("Jednoelementowe zbiory\n");
         printf("Ile ma ich byc\n");
         scanf("%d",&ilosc);
         createSets(ilosc);
         break;
  case 2:
         printSets(ilosc);
    break;
  case 3:
         printf("\nktore zbiory chcesz polaczyc\n");
         scanf("%d",&t1);
         scanf("%d",&t2);
         if(t1 > ilosc){
           return 0;
         }
         if(t2 > ilosc){
           return 0;
         }
         Union(FindSet(Z[t1]), FindSet(Z[t2]));
    break;
 case 4:
      return 0;
    break;
  }
  }
         return 0;
}
