#include <stdio.h>

void converterbinario(int n){
  
  if (n>0 && n/2){
    converterbinario(n/2);
  
  }
  printf("%d\n",n%2);
  }
  int main(){
    converterbinario(11);
  
    
  return 0;

  

}