#include <stdio.h>


  struct pessoa{
    char nome[100];
    int idade;
    float altura;
    double peso;
    int nascimento;
  };
  int main(){
    printf("digite seus dados\n");
    struct pessoa p;
    scanf("%s\n",p.nome);
    scanf("%d",&p.idade);
    scanf("%f",&p.altura);
    scanf("%lf",&p.peso);
    scanf("%d",&p.nascimento);
  


  printf("nome: %s,idade: %d,altura: %.1f,peso :%.1lf,nasc: %d\n",p.nome,p.idade,p.altura,p.peso,p.nascimento);
  printf("obrigado por informa seus dados\n");
  return 0;
}