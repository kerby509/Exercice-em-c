#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXELE 20
#define OVERFLOW 5

typedef struct {
  int id;
  char nome[41];
  double salario;
  int idade;
}Funcionario;

//struct func funcionario[MAXELE+OVERFLOW];
int hash(int id){
  return id%MAXELE;
}
//imprimir lista
void initHashtable(Funcionario *h){
  int i;
  for(i=0;i<MAXELE+OVERFLOW;i++)
      h[i].id=-1;
}
void printHtable(Funcionario *h){
  int i;
    printf("Hash Table:\n");
    for (i=0;i<MAXELE;i++){
      if(h[i].id!=-1){
        printf(" %d\n",h[i].id);
        printf(" %s\n",h[i].nome);
        printf(" %lf\n",h[i].salario);
        printf(" %d\n",h[i].idade);
      }
      else printf("espaco disponivel\n");
    }   
        printf("Overflow:\n");
    for (i=MAXELE;i<MAXELE+OVERFLOW;i++){
      if(h[i].id!=-1){
        printf(" %d\n",h[i].id);
        printf(" %s\n",h[i].nome);
        printf(" %lf\n",h[i].salario);
        printf(" %d\n",h[i].idade);
      }
      else printf("espaco disponivel\n");
    }
}

  Funcionario insereFunc(){

    Funcionario h;
  //for (int i=0; i<MAXELE+OVERFLOW;i++)
    printf("Id: ");
    scanf("%d",&h.id);
    printf("Nome: ");
    scanf("%s",h.nome);
    printf("Salario: ");
    scanf("%lf",&h.salario);
    printf("Idade: ");
    scanf("%d",&h.idade);
    return h;
  }

//usei as ideias que estão no moodle

  int main(){
    Funcionario h;
    Funcionario hTable[MAXELE+OVERFLOW];
    int id, pos, found,i,j;

  int continuar=1;
  initHashtable(hTable);

  while(continuar!=0){
  printf("**Digite uma opcão valida\n");
  printf("1. Incluir os dados\n");
  printf("2. Lista Dos Elementos\n");
  printf("0. Sair\n");
  scanf("%d", &continuar);

  if (continuar == 1) {
      printf("1. Incluir os dados\n");
      h=insereFunc();
      pos=hash(h.id);
      if(hTable[pos].id==-1)
        hTable[pos]=h;
      else{
        found=0;
        for(i=MAXELE;i<MAXELE+OVERFLOW;i++){
          if(hTable[pos].id==-1){
            hTable[pos]=h;
            found=1;
          }
        }
        if (found==0)
            printf("area do OVERFLOW cheia\n");
      }
  }
  else  printHtable(hTable);

  }
  return 0;

}