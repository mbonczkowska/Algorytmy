#include <stdio.h>
#include <string.h>
 
 
int n,m;
 
void PrintLCS(char b[][1000], char *X, int i, int j){
 
  if(n == 0 || j == 0) return;
  if(b[i][j] == '\\'){
    PrintLCS(b,X,i-1,j-1);
    printf("%c",X[i]);
  }
  else{
    if(b[i][j] == '|') PrintLCS(b,X,i-1,j);
    else PrintLCS(b,X,i,j-1);
  }
}
void LCS_Lenght(char *X, char *Y){
 
 
 
  int c[1000][1000];
  char b[1000][1000];
  int i,j;
  m = strlen(X);
  n = strlen(Y);
 
  for(i = 0; i < m; i++)
    { c[i][0] = 0; b[i][0] = '0'; } /*c[0][0]\nc[1][0]\nc[2][0]*/
  for(j = 0; j < n; j++)
    { c[0][j] = 0; b[0][j] = '0'; }/*c[0][0]\tc[0][1]*/
 
  for(i = 1; i < m; i++){
    for(j = 1; j < n; j++){
      if(X[i] == Y[j]){
        c[i][j] = c[i-1][j-1] + 1;
        b[i][j] = '\\';
 
      }
      else{
        if(c[i-1][j] >= c[i][j-1]){
         c[i][j] = c[i-1][j];
          b[i][j] = '|';
        }
        else{
          c[i][j] = c[i][j-1];
          b[i][j] = '-';
        }
      }
    }
  }
  /* printf("X = %s\tY = %s\n", X, Y);*/
  printf("nwp: ");
  PrintLCS(b,X,m-1,n-1);
  printf("\n");
 
}
int main(){
 
  char X[1024],Y[1024];
  char x[1024],y[1024];
  int dl_x;
  int dl_y;
 
  X[0] = '0';
  Y[0] = '0';
  printf("Podaj pierwszy ciag: ");
  scanf("%s",x);
  printf("Podaj drugi ciag: ");
  scanf("%s",y);
  dl_x = strlen(x);
  dl_y = strlen(y);
  strncat(X,x,dl_x);/*dopisuje konkretna ilosc znakow*/
  strncat(Y,y,dl_y);
  /*printf("%s %s",X,Y);*/
  LCS_Lenght(Y,X);
  return 0;
}
