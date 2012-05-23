#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int* CPF(char P[])
{
  int m = strlen(P);
  int *pi;
  int q,k = 0;
  pi = (int*)malloc(100*sizeof(int));
  pi[0] = 0;
  pi[1] = 0;

  for ( q = 2 ; q < m ; q++ )
    {
      while ( k > 0 && P[k+1] != P[q] ) /* druga != trzeciej*/
         k = pi[k];
      if ( P[k+1] == P[q] )
         k = k+1;
     pi[q] = k;
    }
   return pi;
}
void KMP_Matcher(char T[],char P[])
{
  int n = strlen(T); /* tresc */
  int m = strlen(P); /* wzorzec */
  int *pi;
  int i,q=0,licz=0;

   pi = CPF(P);

      for ( i = 1 ; i <= n ; i++ )
       {
        while ( q>0 && P[q+1] != T[i] ) /* druga != drugiej */
          q = pi[q];

        if ( P[q+1] == T[i] )
          q = q+1;

        if ( q+1 == m )
         {
          licz = licz+1;
          q = pi[q];
         }
       }
      printf("Wzorzec wystepuje %d razy\n",licz);
}

int main()
{
  char T[] = "abcdabc"; /*tekst*/
  char P[] = "abc"; /*wzorzec*/

  KMP_Matcher(T,P);
}

