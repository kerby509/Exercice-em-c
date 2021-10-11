#include <stdio.h>

int main(void) {
  int i;
  char string[20];
  scanf("%s",string);
  for(int j='a';j<'z';j++)
  printf("%c -> %c\n",j,j-32);

  printf("%s\n",string);
  return 0;
}