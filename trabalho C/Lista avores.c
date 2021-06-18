
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinTreeNode {
    char key;
    struct BinTreeNode *left;
    struct BinTreeNode *right;
} BinTreeNode;

BinTreeNode *BinTreeRebuild(char preordemEst[], int rootIndex, int *qtdNos) {
    BinTreeNode *root;
    int qtdNosSubarv;

    // Consideramos o seguinte caso base nesta funcao recursiva:
    
    // pre-ordem estendido eh negativo
    if (rootIndex < 0) {
        return NULL;
    }

    root = malloc(sizeof(BinTreeNode));
    root->key = preordemEst[rootIndex];
    root->left = NULL;
    root->right = NULL;

    *qtdNos = 1;

    if (preordemEst[rootIndex + 1] != '0') {
        root->left = BinTreeRebuild(preordemEst, rootIndex + 3, &qtdNosSubarv);
        *qtdNos += qtdNosSubarv;
    }

    if (preordemEst[rootIndex + 2] != '0') {
        root->right = BinTreeRebuild(preordemEst, rootIndex + (*qtdNos * 3), &qtdNosSubarv);
        *qtdNos += qtdNosSubarv;
    }

    return root;
}



void preordem(BinTreeNode *root){

  if(root!=NULL){ 
    printf("%s\n",&root->key);
    preordem(root->left);
    preordem(root->right);
    }

}

void inordem(BinTreeNode *root){
  if(root!=NULL){
    inordem(root->left);
    printf("%c",root->key);
    inordem(root->right);

  }
}

void posordem(BinTreeNode *root){
  if(root!=NULL){
    posordem(root->left);
    posordem(root->right);
    printf("%c",root->key);

  }
}

void freeTree(BinTreeNode *root)
{
	if (root==NULL) return;
	freeTree(root->left);
	freeTree(root->right);
  printf("%d",0);
    free(root);
 
}

int main() {
    int qtdNos;
    int tamPreordemEst;
    char *preordemEst = NULL;
    BinTreeNode *root;

    // Le a quantidade de nos da arvore binaria
    scanf("%d", &qtdNos);

    tamPreordemEst = qtdNos * 3;
    preordemEst = malloc((tamPreordemEst + 1) * sizeof(char));

    // Le o percurso em pre-ordem estendido da arvore binaria
    scanf("\n");
    fgets(preordemEst, tamPreordemEst + 1, stdin);
    preordemEst[strcspn(preordemEst, "\n")] = '\0';
   
    
    
    // Reconstroi a arvore binaria a partir do seu percurso em pre-ordem
    // estendido
    if (qtdNos > 0) {
        root = BinTreeRebuild(preordemEst, 0, &qtdNos);
    }
    else {
        root = NULL;
    }

    //Faça a magia acontecer
        inordem(root);
        printf("\n");
        posordem(root);
        printf("\n");
        //preordem(root);
        
        freeTree(root);
        printf("\n");


    return 0;
}
