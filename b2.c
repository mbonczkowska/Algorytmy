#include <stdio.h>
#include <stdlib.h>
#define T 2


int t=T;

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
   static int o=0;

    int i=0;
    

    printf("\nnode%d[label = \"<f0>%c |<f1> %c|<f2> %c\"];",o,x->key[1],x->key[2],x->key[3]);

   
    if(o==2){
      printf("\n\"node%d\":f0 -> \"node%d\":f1;",o-2,o);
      printf("\n\"node%d\":f0 -> \"node%d\":f0;",o-2,o-1);
    }
    if(o==3){
      printf("\n\"node%d\":f2 -> \"node%d\":f0;",o-1,o);
    }

    o++;
    if(x->leaf!=1)
    for(i=1;i<x->n+2;i++)
        B_Tree_Print(x->c[i]);
}

/*WSTAWIANIE #2*/
void B_Tree_Split_Child(struct node *x, int i, struct node *y) {
  /*
   x niepelny wezel wewnetrzny
   i indeks
   y pelny wezel wewnetrzny
   */
  struct node *z=Allocate_Node(); /* przydziela nowy wezel z */
  int j;
  z->leaf = y->leaf;
  z ->n = T - 1; /* nowy wezel musi miec t -1 kluczy */
  for(j=1; j<t; j++) /* kopiuje "polowe prawego" y do z */
    z->key[j] = y->key[t+j];

  if(!y->leaf) { /* kopiuje wskazniki dziecka jesli nie sa liscmi */
    for(j=1; j<t+1; j++)
      z->c[j] = y->c[t+j];
  }
  y->n=t-1; /* po odcieciu prawej polowy y jest t-1 kluczy */
  for(j=(x->n+1); j>i; j--) /* przesuniecie wszytkich x od i */
    x->c[j+1] = x->c[j];  /* przyklejenie nowego dziecka w x */
    x->c[i+1]=z;
    /* klucze musza byc przesuniete rowniez tak samo */
  for(j=x->n; j>i-1; j--)
    x->key[j+1] = x->key[j];
  x->key[i] = y->key[t];
  x->n+=1;
  return;
}
/*WSTAWIANIE #1*/
void B_Tree_Insert_Nonfull(struct node *x, int k) {
  int i=x->n;

  if(x -> leaf) {
    /* przesuniecie w prawo */
    while( i >= 1 && k < x -> key[i] ) {
      x -> key[i+1] = x -> key[i];
      i = i - 1;;
    }

    x -> key[i+1] = k;
    x -> n = x -> n + 1;

  }
 else{
    /* znajdz dziecko gdzie nalezy nowy klucz */
    while( i >= 1 && k < x -> key[i] )
      i = i - 1;
    i = i + 1;
    if(x -> c[i] -> n == (T*2)-1) {
      /*jesli dziecko wezla jest pelne musimy je podzielic */
      B_Tree_Split_Child(x, i, x->c[i]);
      /* jesli x -> c[i] i x -> c[i+1] to nowe dzieci*/
      /* i x->key[i] zostalo zmienione */
      /* zobaczy jesli k nalezy w pierwszym czy ostanim */
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
    /*korzen jest pelen i trzeba podzielic go*/
    struct node *s=Allocate_Node();
    *head = s; /* nowy korzen glowny */
    s->leaf = 0; /* bedzie mial lisc */
    s->n = 0;
    s->c[1] = r; /* dziecko to stary wezel glowny */
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
int main(){
  int inputc[7];
  int i;
  char input[7] = {'b','c','a','d','e','f','g'};
  root=NULL;
  B_Tree_Create(&root);

  for(i=0;i<7;i++)
    inputc[i]=(int)input[i];
  for(i=0;i<7;i++)
  B_Tree_Insert(&root,inputc[i]);
  printf("digraph G{\n");
  printf("node [shape = record,height=.1];\n");
  B_Tree_Print(root);
  printf("\n}");

  return 0;
}


