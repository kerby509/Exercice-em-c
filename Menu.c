#include <stdio.h>




int main()
{
  int continuar;
  
  printf("\n***Digita uma opcao valida!***\n");
  printf("1. Incluir elemento\n");
  printf("2. Excluir elemto\n");
  printf("3. Lista de todos na ordem\n");
  printf("4. Lista de todos na ordem inversa\n");
  printf("5. Apresentar elemento\n");
  printf("0. Sair\n");
  printf("----------------------------\n");
  scanf("%d", &continuar);


  switch(continuar){
    case 1: 
    printf("1. Incluir elemento\n");
      break;
      
      case 2:
      printf("2. Excluir elemto\n");
      break;

      case 3:
      printf("3. Lista de tods na ordem\n");
        break;
            
      case 4:
      printf("4. Lista de todos na ordem inversa\n");
        break;
        
        case 5:
        printf("5. Apresentar elemento\n");


        case 0:
          printf("0. Sair\n");

        break;

        default:
      printf("Digite uma opcao valida\n");
    
        
     //while(continuar);
       //return 0;

    }
}