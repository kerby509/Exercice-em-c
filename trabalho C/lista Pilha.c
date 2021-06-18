#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUNNAME 20

struct tinfo { 
  

  char adress[60];
};

struct tnodo {
  struct tinfo info;
  struct tnodo *down;
};

struct tstack {
  struct tnodo *top;
  struct tnodo *bottom;
};

typedef struct tinfo myinfo;
typedef struct tnodo mynodo;
typedef struct tstack mystack;

//aqui é para print os enderecos
void printPrinterJob(myinfo myst)
{
   	mynodo *n;
    printf("%s\n",myst.adress);
     
    return;
}

void initStack (mystack *st)
{
	st->top=NULL;
	st->bottom=NULL;
	return;
}
//
int isEmpty(mystack *st)
{
    if (st->top==NULL)  
       return 1;
    else
       return 0;
}

void push (mystack *st, myinfo printJob)
{
	mynodo *n;
	n=(mynodo *) malloc(sizeof(mynodo));
	char adress[60];
  
  
	strcpy(n->info.adress,printJob.adress);
	n->down=NULL;
	if (isEmpty(st)) 
	{
		st->top=n;
		st->bottom=n;
	}
	else 
	{
	    n->down=st->top;
	    st->top=n;
    }
	return;
}
void cleanStack(mystack *st)
{
    mynodo *nodo=st->top, *prev;
    if (isEmpty(st))
    {
        printf("Vazio!\n");
        return;
    }
    while (nodo!=NULL)
    {
		prev=nodo;
		nodo=nodo->down;
		free(prev);
	}
	initStack(st);
	return;
}

myinfo pop(mystack *st)
{
	myinfo myst;
	mynodo *n=st->top;
	if (isEmpty(st))
	{
		printf("vazio\n");
    printf("!\n"); 
		strcpy(myst.adress,""); 
		return myst;
	}
	myst=n->info;
	if (st->top==st->bottom) 
	{
		//free(n);
		initStack(st);
		return myst;
    }
	st->top=st->top->down; 
	return myst;
  	free(n);
}
void printAllItens (mystack *st)
{
    mynodo *nodo=st->top; 
    myinfo myst;
    while (isEmpty(st)==0)
    {
		myst=pop(st);
		printPrinterJob(myst);
	}
    return;
}
  int main(){
  
  
  mystack mystck;
	myinfo  mprinter;

	int i;
  
  
   char continuar[100]={"B"};
   	initStack(&mystck);
       
  while(1){

  scanf("%s", continuar);
  if(strcmp(continuar,"E")==0)
      break;

  if(strcmp(continuar,"B")!=0){
    push(&mystck,mprinter);

  }
  else{
        
    	  mprinter=pop(&mystck);
        printf("%s\n",mprinter.adress);  
        
  }
  }
	//
	
   return 0;	
}
