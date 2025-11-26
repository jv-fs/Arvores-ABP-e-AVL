#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad_AVL.h"

static int rotAVL = 0; //Diferentemente do caso da ABP, aqui haverá rotações, então teremos duas variáfveis globais
static int cmpAVL = 0;

//Função que forem iguais às árvores ABPs em estrutura serão relaxadas em comentários para não repetir muito o que já foi explicado

NodoAVL* CriaArvoreAVL()
{
    return NULL;
}

NodoAVL* RotacaoDir(NodoAVL *p) //Código extraído da aula 18 AVL (página 31). A função não foi modificada e realiza uma rotação simples à direita
{
    NodoAVL *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

NodoAVL* RotacaoEsq(NodoAVL *p) //Código extraído da aula 18 AVL (página 39). A função não foi modificada e realiza uma rotação simples à esquerda
{
    NodoAVL *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

NodoAVL* RotacaoDuplaDir(NodoAVL *p) //Código extraído da aula 18 AVL (página 46). A função não foi modificada e realiza uma rotação dupla à direita
{
    NodoAVL *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}

NodoAVL* RotacaoDuplaEsq(NodoAVL *p) //Código extraído da aula 18 AVL (página 56). A função não foi modificada e realiza uma rotação dupla à esquerda
{
    NodoAVL *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
    else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    p = y;
    return p;
}

NodoAVL* Caso1(NodoAVL *a, int *ok) //Código extraído da aula 18 AVL (página 71). A função não foi modificada e realiza as rotações respeitando o fator de balanceamento da subárvore à esquerda para rotar à direita
{
    NodoAVL *z;
    z = a->esq;

    if (z->FB == 1)
    {
        a = RotacaoDir(a);
    }
    else
    {
        a = RotacaoDuplaDir(a);
    }

    a->FB = 0;
    *ok = 0;
    return a;
}

NodoAVL* Caso2(NodoAVL *a, int *ok) //Código extraído da aula 18 AVL (página 72). A função não foi modificada e realiza as rotações respeitando o fator de balanceamento da subárvore à direita para rotar à esquerda
{
    NodoAVL *z;
    z = a->dir;

    if (z->FB == -1)
    {
        a = RotacaoEsq(a);
    }
    else
    {
        a = RotacaoDuplaEsq(a);
    }

    a->FB = 0;
    *ok = 0;
    return a;
}


NodoAVL* InsereArvoreAVL(NodoAVL *a, char x[], float tempo, int *ok) //Código extraído da aula 18 AVL (página 70). As modificações serão destacadas, mas o código é essencialmente o mesmo
{
    if (a == NULL)
    {
        a = (NodoAVL*)malloc(sizeof(NodoAVL));
        strcpy(a->nome, x); //Chave armazenada por strcpy, como na ABP
        a->horas = tempo;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcasecmp(x, a->nome) < 0) //Comparação utilizando strcasecmp, como na ABP
    {
        a->esq = InsereArvoreAVL(a->esq, x, tempo, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = Caso1(a, ok); //O caso 1 realiza as rotações à direita (simples ou dupla)
                rotAVL = rotAVL + 1; //Como uma rotação dupla equivale a uma rotação só, é aqui que colocamos o contador de rotações

                break;
            }
        }
    }
    else
    {
        a->dir = InsereArvoreAVL(a->dir, x, tempo, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a, ok); //O caso 2 realiza as rotações à esquerda (simples ou dupla)
                rotAVL = rotAVL + 1; //Como uma rotação dupla equivale a uma rotação só, é aqui que colocamos o contador de rotações
                break;
            }
        }
    }
    return a;
}

int ContaNodosAVL(NodoAVL *a) //É uma função bem simples. Ela simplesmente sai varrendo a árvore e somando 1 ao retorno para computar o número de nodos na árvore (que corresponde à quantidade de elementos no DataSet)
{
    if(a == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + ContaNodosAVL(a->esq) + ContaNodosAVL(a->dir);
    }
}

int AlturaAVL(NodoAVL *a) //Função extraída do laboratório de balanceamento de árvores binárias (não foram feitas alterações)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = AlturaAVL(a->esq);
        Alt_Dir = AlturaAVL(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

NodoAVL* ConsultaAVL(NodoAVL *a, char ch[]) //A função de consulta é idêntica à da ABP. Consiste na função disponível no enunciado do trabalho com o strcasecmp como modificação
{
    while (a != NULL)
    {
        cmpAVL++;
        int comparacao = strcasecmp(a->nome, ch);
        if (comparacao == 0)
        {
            return a;
        }
        else
        {
            if (comparacao > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }
    return NULL;
}

int GetRotacoesAVL() //Da mesma forma que na ABP, retornamos as variáveis globais rotAVL e cmpAVL por meio de um Get
{
    return rotAVL;
}

int GetComparacoesAVL()
{
    return cmpAVL;
}

void DestroiArvoreAVL(NodoAVL *a) //É somente um algoritmo de destruição da árvore. Ele utiliza um caminhamento pós-fixado.
{
    if(a != NULL)
    {
        DestroiArvoreAVL(a->esq);
        DestroiArvoreAVL(a->dir);
        free(a);
    }
}
