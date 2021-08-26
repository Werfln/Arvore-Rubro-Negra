#include <stdio.h>
#include <stdlib.h>
#include <funcoes.h>
#include <time.h>

int main()
{
    rn T = CriarArvore();
    int nA = 100;
    int nR = 10;
    int aux = 0;
    int *chaves = (int *) malloc(sizeof(int) * (nA));

    //Geração de n números para adicionar à arvore rubro-negra
    for (int i = 0; i < nA; i++)
    {
        chaves[i] = i+1;
        InserirRN(T,chaves[i]);
        printf("\nArvore apos a adicao:");
        preOrdem(T);
    }


    printf("\n--------------------------------------->REMOVER<---------------------------------------\n");

    //Geração de n números de chaves para remover da arvore rubro-negra
    for (int i = 0; i < nR; i++)
    {
        chaves[i] = aux;
        remover(T,aux);
        printf("Arvore apos a remocao");
        preOrdem(T);
    }

    free(chaves);
    return 0;
}
