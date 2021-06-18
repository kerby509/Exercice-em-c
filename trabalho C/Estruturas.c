#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

struct aluno{
  char matricula[11];
  char nome[41];
  Data nascimento;
  float media;  

  struct aluno *next;
}; 
//funcão pra inprimir alunos
typedef struct aluno Aluno;
//structura  de data
void updateData(Data *dt, int d,int m, int a)
{
  dt->dia=d;
  dt->mes=m;
  dt->ano=a;
}
void printData(Data d)
{
  printf("Data: %d/%d/%d\n",d.dia,d.mes,d.ano);
}

void printStudent(Aluno *p)
{
  Aluno *aux;
  for (aux=p;aux!=NULL;aux=aux->next)
  {
    printf("Matricula: %s\n",aux->matricula);
    printf("Nome: %s\n",aux->nome);
    printData(aux->nascimento);
    printf("Nota: %.2f\n",aux->media);

    printf("--------------\n");
  }

  //usei as ideias do codigo que está no moodle
}
Aluno *getLast(Aluno *p)
{
  Aluno *aux=p;
  for (aux=p;aux->next!=NULL;aux=aux->next);
  return aux;
}
Aluno *getStudent(Aluno *f)
{
  Aluno *p, *aux;
  int d,m,a;
  p=(Aluno *)malloc(sizeof(Aluno));
  //printf("Matricula: ");
  scanf("%s",p->matricula);
  //printf("Nome: ");
  scanf("%s",p->nome);
 // printf("Nascimento: ");
  scanf("%d %d %d",&d,&m,&a);
  updateData(&p->nascimento,d,m,a);
  //printf("Nota: ");
  scanf("%f",&p->media);


  p->next=NULL;
  if (f==NULL)
     f=p;
  else
  {
    aux=getLast(f);
    aux->next=p;
  }
  return f;
}
//funcão pra remover student
struct Aluno *next;
Aluno *deleteStudent(Aluno *p){
  char key[11];
 Aluno *aux=p ,*prev=p;
 //printf("digita a matricula a ser excluido\n");
 scanf("%s",key);
 while (strcpy(aux->matricula,key)!=0 && aux!=NULL){
   prev=aux;
   aux=aux->next;
   if(aux==NULL){
     printf("\n");
     return p;
   }
    else{
      prev->next=aux->next;
    }
  if (aux==p)
     aux=aux->next;
  free(aux);
  return p;
    }
    return p;
}
   

 

//funcão lista tds 
void listatodos(Aluno *p){
  Aluno *aux;
  aux=p;
  if(aux==NULL){
    printf("Lista Vazia!\n");
  }
  else{
    while (aux!=NULL){
      printf("%s, %s, %d/%d/%d, %.2f\n",aux->matricula,aux->nome,aux->nascimento.dia,aux->nascimento.mes,aux->nascimento.ano,aux->media);
      aux=aux->next;
    }
  }
}
  //funcao para inverta
  Aluno *inversaolista(Aluno *p){
    Aluno *aux;
  Aluno *inverta(Aluno *aux);
  Aluno *prev,*atual;
  prev=NULL;
  atual=p;
  while (prev!=NULL){
    prev=atual->next;
    atual->next=aux;
    aux=aux->next;
    prev=atual;
     printf("%s, %s, %d/%d/%d, %.2f\n",aux->matricula,aux->nome,aux->nascimento.dia,aux->nascimento.mes,aux->nascimento.ano,aux->media);
        
  }
  return prev;

}
//apresentar todos elemntos
void apresentaElentos(Aluno *p){

}




int main()
{

  Aluno *p, *first=NULL, *aux;
  int continuar=1;
  while(continuar!=0){
  
  
  scanf("%d", &continuar);

  if (continuar == 1) {
  //printf("1. Incluir elemento\n");
      first=getStudent(first);
  }
  if (continuar == 2) {
    deleteStudent(first);
  //printf("2. Excluir elemto\n");
  }

if (continuar == 3) {
  listatodos(first);
  //printf("3. Lista de todos na ordem\n");
}

if (continuar == 4) {
  inversaolista(first);
  //printf("4. Lista de todos na ordem inversa\n");
}
if (continuar==5){
   // printf("5. Apresentar elemento\n");
}
if (continuar==0){
    //printf("0. Sair\n")

    return 0;
}
}
return 0;


}