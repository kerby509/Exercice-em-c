#include <stdio.h>

int main(void) {
  int matriz[4][4];
  int soma=0;
  for(int i=0;i<4;i++)
    for (int j=0;j<4;j++)
    scanf("%d",&matriz[i][j]);

  for(int i=0;i<4;i++){
    for (int j=0;j<4;j++){
      if(j==i){
      soma+=matriz[i][j]+soma;
      }

  printf("\t%d",soma);
    }
  printf("\n");
    
  }
  return 0;
}