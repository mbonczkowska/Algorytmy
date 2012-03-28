
#include <stdio.h>
#include <stdlib.h>
#define T 2

static int t=T;

struct node {
  int n;  /* liczba kluczy*/
  char key[2*T];/*klucze*/
  int leaf; /* czy wezel jest lisciem */
  struct node *c[2*T+1]; /* tablica wskaznikow do synow */
};

struct node *root;

/*PRZYDZIELANIE PAMIECI*/
struct node *Allocate_Node(void) {
  return (struct node *) malloc(sizeof(struct node));
}

/*WYSWIETLANIE b-DRZEWA*/
void B_Tree_Print(struct node *x){
  int i=1;
  static int k=0;
  k++;
  for(i=1;i<x->n+1;i++){

    printf("%c [shape=record, label=%c]; %i\n",x->key[i],x->key[i],i);
    if(i==2)
      printf("%c -> %c;\n",x->key[i],x->key[(i+1)/2]);
    if(i==3)
      printf("%c -> %c;\n",x->key[(i+1)/2],x->key[i]);

  }
  printf("\n");

  if(x->leaf!=1)
    for(i=1 ; i < x->n+2; i++){

      B_Tree_Print(x->c[i]);

    }

}

/*WSTAWIANIE #2*/
void B_Tree_Split_Child(struct node *x, int i, struct node *y) {
  struct node *z=Allocate_Node();
  int j;
  z->leaf=y->leaf;
  z ->n = T - 1;
  for(j=1; j<t; j++)
    z->key[j] = y->key[t+j];
  if(!y->leaf) {
    for(j=1; j<t+1; j++)
      z->c[j] = y->c[t+j];
  }
  y->n=t-1;
  for(j=(x->n+1); j>i; j--)
    x->c[j+1] = x->c[j];
  x->c[i+1]=z;
  for(j=x->n; j>i-1; j--)
    x->key[j+1] = x->key[j];
  x->key[i] = y->key[t];
  x->n+=1;
  return;
}

/*WSTAWIANIE #1*/
void B_Tree_Insert_Nonfull(struct node *x, int k) {
  int i;
  i=x->n;

  if(x -> leaf) {
    while( i >= 1 && k < x -> key[i] ) {
      x -> key[i+1] = x -> key[i];
      i = i - 1;;
    }
    x -> key[i+1] = k;
    x -> n = x -> n + 1;
    printf("\nKlucz %c zostal wstawiony.\n", k);
    getchar();
    getchar();
  }
  else{
    while( i >= 1 && k < x -> key[i] )
      i = i - 1;
    i = i + 1;
    if(x -> c[i] -> n == (T*2)-1) {
      B_Tree_Split_Child(x, i, x->c[i]);
      if( k > x->key[i] )
        i= i + 1;
    }
    B_Tree_Insert_Nonfull(x->c[i], k);
  }
  return;
}

/*WSTAWIANIE ELEMENTU*/
void B_Tree_Insert(struct node **head, int k) {
  struct node *r=*head;
  if(r -> n == 2 * t - 1) {
    struct node *s=Allocate_Node();
    *head = s;
    s->leaf = 0;
    s->n = 0;
    s->c[1] = r;
    B_Tree_Split_Child(s, 1, r);
    B_Tree_Insert_Nonfull(s, k);
  }
  else
    B_Tree_Insert_Nonfull(r, k);
  return;
}

/*TWORZENIE B-DRZEWA*/
void B_Tree_Create(struct node **head) {
  struct node *x=Allocate_Node();
  x->leaf=1;
  x->n=0;
  *head=x;
  return;
}
int menu(){
  int c,inputc;
  char input;
  system("clear");
  printf("\tB-DRZEWA\n\nPodaj dzialanie:\n\n");
  printf("1 - Wstawienie elementu\n");
  printf("2 - Wypisz klucze\n");
  printf("q - Koniec\n\n");
  c=getchar();
  switch (c){
  case '1':{
    printf("\nPodaj litere : ");
    scanf("%s",&input);
    inputc=(int)input;
    B_Tree_Insert(&root,inputc);
    menu();
    break;
  }

  case '2':{
    printf("\n\nWyswietlanie:\n\n");
    printf("digraph G{\n");
    B_Tree_Print(root);
    printf("\n}");
    getchar();
    getchar();
    menu();
    break;
  }

  case 'q':
    return 0;
  default :
    menu();
  }
  return 0;
}
int main(){
  root=NULL;
  B_Tree_Create(&root);
  menu();
  return 0;
}
