#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT 100
typedef struct {
  int dia;
  int mes;
  int ano;
} Date;

struct paciente{
  char name[30];
  Date birth;
  char email[60];
  char phone[15];
   struct paciente *next;
	 struct paciente *prev;
};

typedef struct paciente Paciente;
//função estrutura de data
void updateDate(Date *dt, int d,int m, int a)
{
  dt->dia=d;
  dt->mes=m;
  dt->ano=a;
}
void printDate(Date d)
{
  printf("Data: %d/%d/%d\n",d.dia,d.mes,d.ano);
}

//funcao listacontact
void listacontact(Paciente *p){
  Paciente *plist;
  if(p==NULL){
    printf("NÃO ENCONTRADA\n");
    return;
  }
    for(plist=p; plist!=NULL; plist=plist->next){
      printf("Name: %s\n",plist->name);
      printDate(plist->birth);
      printf("Email: %s\n",plist->email);
      printf("Phone:%s\n",plist->phone);

    
    }
}

//função para Inserir contato
Paciente *inscontact(Paciente *p){
  Paciente *plist;
  int d,m,a;

  plist=(Paciente *)malloc(sizeof(Paciente));
  printf("Name: ");
  fgets(plist->name, 40, stdin);
  printf("Date of birth: ");
  scanf("%d %d %d",&d,&m,&a);
  updateDate(&plist->birth,d,m,a);
  printf("Email: ");
  scanf("%s",plist->email);
  printf("Phone: ");
  scanf("%s",plist->phone);
 
  plist->prev = NULL;
  plist->next = NULL;
  
  if(p!=NULL){ 
    Paciente *ultimo = p;
    while(ultimo->next != NULL){ 
      ultimo = ultimo->next;
    }
    
    ultimo->next = plist;
    plist->prev = ultimo; 
  } else{
      p = plist;
    }
  return p;  
}

//Insert contact posicionado

Paciente *contactposicionado(Paciente *p){
  Paciente *plist;
  char key[11];
  Paciente *aux=p ,*prev=p;
  printf("digite o email a ser posicionado\n");
  scanf("%s",key);


  while(strcmp(aux->email,key)!=0 && aux!=NULL){
    aux=aux->next;
    if(aux==NULL){
      printf("Email não encontrada\n");
      return p;
    }
    else{
      
      prev->next=aux->prev;
      aux->next=prev;
      
    }
    if(aux==p){
      aux=aux->next;
    
      return p;
    }
  }
  return p;

}
//funcao excluircontact

Paciente *excluircontact(Paciente *p){
  Paciente *plist;

  char chave[11];
  Paciente *aux=p ,*prev=p;
  printf("digite o email a ser excluido\n");
  scanf("%s",chave);

   //while (aux->email!=chave && aux!=NULL)
    while(strcmp(aux->email,chave)!=0 && aux!=NULL)

  {
    prev=aux;
    aux=aux->next;
  
  }
    if (aux==NULL)
  {
    printf("Email não encontrado!\n");
    return p;
  }
  prev->next=aux->next;

  if (aux==p)
     p=aux->next;
     p=aux->prev;
  free(aux);
  return p;
}


int main()
{
  Paciente *head=NULL, *tail=NULL;

  int op=1;
  while(op!=0)
  {

  
  
  printf("\n***Digita uma opcao valida!***\n");
  printf("1. Inserir contatos\n");
  printf("2. Inserir contatos posicionado\n");
  printf("3. Deletar contato\n");
  printf("4. Listar os contatos\n");
  printf("5. Consultar um contato (pelo nome)\n");
  printf("6. Atualizar os campos de um contato\n");
  printf("0. Sair\n");
  printf("----------------------------\n");
  scanf("%d", &op);
  getchar();


  switch(op){
    case 1: 
    printf("Inserir contatos\n");
    head=inscontact(head);
      break;
      
      case 2:
      printf("Inserir contatos posicionado\n");
      

      contactposicionado(head);
      break;

      case 3:
      printf("Deletar contato\n");
        excluircontact(head);
        //delContact(head);
        break;
            
      case 4:
      printf("Listar os contatos\n");
        listacontact(head);

        break;
        
        case 5:
        printf("Consultar um contato (pelo nome)\n");


        case 6:
          printf(" Atualizar os campos de um contato\n");

        break;

        case 0:
          printf("Sair\n");

        break;

    }  
        
  }

  return 0;
}


