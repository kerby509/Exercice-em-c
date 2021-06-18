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

  struct aluno *prev;
  struct aluno *next;
}; 
typedef struct aluno Aluno;
// strutura de data
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

//funcao para inclui elemento
void printstudent(Aluno *p){
  Aluno *plist;
  if(p==NULL){
    printf("Lista Vazia!\n");
    return;
  }
    for(plist=p; plist!=NULL; plist=plist->next){
      printf("Matricula: %s\n",plist->matricula);
      printf("Nome: %s\n",plist->nome);
      printData(plist->nascimento);
      printf("Nota: %.2f\n",plist->media);

      printf("--------------\n");
    }
}

//recebe o primeiro da lista, e retorn o primeiro da lista.
Aluno *getstudent(Aluno *p){
  Aluno *plist;
  int d,m,a;
  plist=(Aluno *)malloc(sizeof(Aluno));
  printf("Matricula: ");
  scanf("%s",plist->matricula);
  printf("Nome: ");
  scanf("%s",plist->nome);
  printf("Nascimento: ");
  scanf("%d %d %d",&d,&m,&a);
  updateData(&plist->nascimento,d,m,a);
  printf("Nota: ");
  scanf("%f",&plist->media);
  plist->prev = NULL;
  plist->next = NULL;
  
  if(p!=NULL){ //faz o encadeamento do novo elemento, no fim da lista
      //percorrer a lista até o final
    Aluno *ultimo = p;
    while(ultimo->next != NULL){ //chega até o último
      ultimo = ultimo->next;
    }
    //faz encadeamento do elemento
    //adicionar o plist no fim da lista, depios do último
    ultimo->next = plist; //coloca plist no fim da lista
    plist->prev = ultimo; //diz que o anterior do plist, é o último. Agora Plist é o novo ultimo
  } else{ // não existe lista, o novo elemento é o primeiro
    p = plist;
  }
  
  return p;
}

// excluir elemento na lista
Aluno *deletestudent(Aluno *p){
  Aluno *plist;
  char key[11];
  Aluno *aux=p ,*prev=p;
  printf("digite a matricula a ser excluido\n");
  scanf("%s",key);
  while(strcpy(aux->matricula,key)!=0 && plist!=NULL){
    //prev=aux;
    aux=aux->next;
    //plist->prev=aux;
    if(aux==NULL){
      printf("Matricula não encontrada\n");
      return p;
    }
    else{
      
      prev->next=aux->prev;
      aux->next=prev;
    }
    if(aux==p){
      aux=aux->next;
      free(aux);
      
      return p;
    }
    return p;
  }
}

//lista todos elemento
void listatodos(Aluno *plist){
  Aluno *aux;
  if(plist==NULL){
    printf("Lista Vazia!\n");
    return;
  }
  else{
    while(plist!=NULL){
    //for(plist=p; plist!=NULL; plist=plist->next){
       printf("%s, %s, %d/%d/%d, %.2f\n",plist->matricula,plist->nome,plist->nascimento.dia,plist->nascimento.mes,plist->nascimento.ano,plist->media);
      plist=plist->next;
    
      

      printf("--------------\n");
    }
    }
    
}
//lista inversa
void inversalista(Aluno *p){
  Aluno *plist;
  if(p==NULL){
    printf("Lista Vazia!\n");
    return;
  }
  else{
    while(plist!=NULL){
  //for(plist=p; plist!=NULL; plist=plist->prev){
    printf("%s, %s, %d/%d/%d, %.2f\n",plist->matricula,plist->nome,plist->nascimento.dia,plist->nascimento.mes,plist->nascimento.ano,plist->media);
      plist=plist->prev;
      //p=plist;
      

      printf("--------------\n");
    }
  
  } 
  
    
}


int main()
{

  Aluno *head=NULL, *tail=NULL;

  int continuar=1;
  while(continuar!=0){
  
  printf("\n***Digita uma opcao valida!***\n");
  printf("1. Incluir elemento\n");
  printf("2. Excluir elemto\n");
  printf("3. Lista de todos a partir do 1ro\n");
  printf("4. Lista de todos a partir ultimo\n");
  printf("0. Sair\n");
  printf("----------------------------\n");
  scanf("%d", &continuar);

  if (continuar == 1) {
  printf("1. Incluir elemento\n");
  head=getstudent(head);
  //printf("\n");
  head=getstudent(head);
  //printstudent(head);
      
  }
  if (continuar == 2) {
    
  printf("2. Excluir elemto\n");
  deletestudent(head);
  }

if (continuar == 3) {
  
  printf("3. Lista de todos a partir do 1ro\n");
  listatodos(head);

}

if (continuar == 4) {
  printf("4. Lista de todos a partir ultimo\n");
  inversalista(head);

}
if (continuar==0){
    printf("0. Sair\n");break;

    //printf("%d\n",continuar);

    return 0;
}
}
return 0;


}
