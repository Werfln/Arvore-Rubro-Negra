#include <stdio.h>
#include <stdlib.h>
#ifndef FUNCOES_H
#define FUNCOES_H

//DETALHE: 'V' significa vermelho e 'N' significa negro.


//Estrutura dos nós da árvore rubro-negra
typedef struct NO *no;
struct NO
{
    int chave;
    char cor;
    struct NO *esquerdo;
    struct NO *direito;
    struct NO *pai;
};
typedef struct NO NO;

struct NO_RN
{
    struct NO *raiz;
};
typedef struct NO_RN *rn;

struct NO *externo = NULL;

int chave[13];

rn CriarArvore()
{
    if (externo == NULL) {
        externo = (no) malloc(sizeof(NO));
        externo->cor = 'N';
        externo->direito = externo;
        externo->esquerdo = externo;
        externo->pai = externo;
    }

    rn no = (rn) malloc(sizeof(rn));
    no->raiz = externo;
    return no;
}

no criarNo(int chave) {
    no novo = (no) malloc(sizeof(NO));
    novo->chave = chave;
    novo->cor = 'V';
    novo->direito = externo;
    novo->esquerdo = externo;
    novo->pai = externo;
    return novo;
}

struct NO *sucessor(NO *x)
{
    while(x->esquerdo != NULL){
        x = x->esquerdo;
    }

    return x;
};

no Buscar(no x,int chave)
{
    if (x == externo || x->chave == chave)
        return x;

    else if (chave < x->chave)
        Buscar(x->esquerdo, chave);

    else
        Buscar(x->direito, chave);

    return x;
}

//Substitui o nó u pelo v
void MoverPai(rn a,no u,no v)
{
    if(u->pai == externo)
        a->raiz = v;

    else if(u == u->pai->esquerdo)
        u->pai->esquerdo = v;

    else
        u->pai->direito = v;

    v->pai = u->pai;
}

// Rotação à esquerdo
void RotaEsquerda(rn a,no x)
{
    //Um novo nó y tem como entrada o nó direito de x
    no y = x->direito;
    x->direito = y->esquerdo;
    if (y->esquerdo != externo)
        y->esquerdo->pai = x;

    y->pai = x->pai;
    if (x->pai == externo)
        a->raiz = y;

    else if (x == x->pai->esquerdo)
        x->pai->esquerdo = y;

    else
        x->pai->direito = y;

    y->esquerdo = x;
    x->pai = y;
}


// Rotação à direito
void RotaDireita(rn a,no x)
{
    //Um novo nó x tem como entrada o nó esquerdo de y
    no y = x->esquerdo;
    x->esquerdo = y->direito;
    if (y->direito != externo)
        x->direito->pai = y;

    y->pai = x->pai;
    if (x->pai == externo)
        a->raiz = x;

    else if (x == x->pai->esquerdo)
        x->pai->esquerdo = y;

    else
        x->pai->direito = y;

    y->direito = x;
    x->pai = y;
}

// Função para fazer as rotações necessárias após a inserção de um novo nó
void Rota(rn a,no z)
{
    no y;
    // Faz a interação enquanto o pai de z é vermelho
    while (z->pai->cor == 'V')
    {
        if (z->pai == z->pai->pai->esquerdo)
        {
            // Encontra o nó tio e o atribui à y
            y = z->pai->pai->direito;
            if (y->cor == 'V')
            {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'V';
                z = z->pai->pai;
            }

            else
            {
                if(z == z->pai->direito)
                {
                    z = z->pai;
                    RotaEsquerda(a,z);
                }

                z->pai->cor = 'N';
                z->pai->pai->cor = 'V';
                RotaDireita(a,z->pai->pai);
            }
        }

        else
        {
            y = z->pai->pai->esquerdo;
            if(y->cor == 'V')
            {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'V';
                z = z->pai->pai;
            }

            else
            {
                if (z == z->pai->esquerdo)
                {
                    z = z->pai;
                    RotaDireita(a,z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'V';
                RotaEsquerda(a, z->pai->pai);
            }
        }
    }

    a->raiz->cor = 'N';
}

// Inserção de nó na árvore rubro-negra
void InserirRN(rn a,int chave)
{
    no x = a->raiz;
    no y = externo;
    no z = criarNo(chave);

    //Faz a interção enquanto o nó não for externo
    while (x != externo)
    {
        y = x;
        if(z->chave == x->chave)
        {
            printf("Chave existente");
        }

         if (z->chave < x->chave)
            x = x->esquerdo;

         else
            x = x->direito;
    }

    z->pai = y;
    if (y == externo)
        a->raiz = z;

    else if (z->chave < y->chave)
        y->esquerdo = z;

    else
        y->direito = z;

    z->esquerdo = externo;
    z->direito = externo;
    z->cor = 'V';

    Rota(a, z);
}

// Função para fazer as rotações necessárias após a remoção de um nó
void RotaRemover(rn a,no x)
{
    no w;
    while(x != a->raiz && x->cor == 'N')
    {
        if(x == x->pai->esquerdo)
        {
            w = x->pai->direito;
            if (w->cor == 'V')
            {
                w->cor = 'N';
                x->pai->cor = 'V';
                RotaEsquerda(a, x->pai);
                w = x->pai->direito;
            }

            if(w->esquerdo->cor == 'N' && w->direito->cor == 'N')
            {
                w->cor = 'R';
                x= x->pai;
            }

            else
            {
                if(w->direito->cor == 'N')
                {
                    w->esquerdo->cor =  'N';
                    w->cor = 'V';
                    RotaDireita(a, w);
                    w = x->pai->direito;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->direito->cor = 'N';
                RotaEsquerda(a, x->pai);
                x = a->raiz;
            }
        }

        else
        {
            w = x->pai->esquerdo;
            if (w->cor == 'V')
            {
                w->cor = 'N';
                x->pai->cor = 'V';
                RotaDireita(a, x->pai);
                w = x->pai->esquerdo;
            }

            if (w->direito->cor == 'N' && w->esquerdo->cor == 'N')
            {
                w->cor = 'V';
                x = x->pai;
            }

            else
            {
                if (w->esquerdo->cor == 'N')
                {
                    w->direito->cor = 'N';
                    w->cor = 'V';
                    RotaEsquerda(a, w);
                    w = x->pai->esquerdo;
                }

                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->esquerdo->cor = 'N';
                RotaDireita(a, x->pai);
                x = a->raiz;
            }
        }
    }

    x->cor = 'N';
}

//Remove o nó
void RemoverRN(rn a,no z)
{
    no y = z;
    no x;
    char corOriginalY = y->cor;
    if(z->esquerdo == externo)
    {
        x = z->direito;
        MoverPai(a, z, z->direito);
    }

    else if(z->direito == externo)
    {
        x = z->esquerdo;
        MoverPai(a, z, z->esquerdo);
    }

    else
    {
        y = sucessor(z->direito);
        corOriginalY = y->cor;
        x= y->direito;
        if(y->pai ==z)
            x->pai = y;

        else
        {
            MoverPai(a, y, y->direito);
            y->direito = z->direito;
            y->direito->pai = y;
        }

        MoverPai(a, z, y);
        y->esquerdo = z->esquerdo;
        y->esquerdo->pai = y;
    }

    if(corOriginalY == 'N')
        RotaRemover(a, x);

    a->raiz->cor = 'N';
}

//Função principal de remoção de uma chave
void remover(rn a,int chave) {
    no z = Buscar(a->raiz, chave);
    no aux = z;
    if (z == externo)
        return;

    else
        RemoverRN(a, z);

    free(aux);
}

// Função para imprimir a árvore
void Imprimir(no x)
{
    if (x == externo)
        return;

    printf("\nChave %d , cor %c (filho de %d)", x->chave, x->cor, x->pai->chave);
    Imprimir(x->esquerdo);
    Imprimir(x->direito);
}

void preOrdem(rn a)
{
    Imprimir(a->raiz);
}

#endif // FUNCOES_H
