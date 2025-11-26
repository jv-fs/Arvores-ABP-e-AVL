#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad_ABP.h"

static int cmpABP = 0; //Variável global que armazena o número de comparações realizada. O static garante que essa variável seja presente apenas no contexto deste arquivo

Nodo* CriaArvoreABP() //Retorna NULL para criar a árvore. É o mesmo processo que já era feito no tópico de listas. Se vazia, aponta pra NULL
{
    return NULL;
}

Nodo* InsereArvoreABP(Nodo *a, char ch[], float horas) //Função extraída da aula 16 ABP (página 15) e adaptada
{
    if (a == NULL)
    {
        a = (Nodo*) malloc(sizeof(Nodo));
        strcpy(a->nome, ch); //Copia a chave e salva no nodo novo
        a->horas = horas;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (strcasecmp(ch, a->nome) < 0) //Adaptação para comparar as chaves. Caso o resultado for negativo, significa que a chave é anterior, lexicograficamente, à chave do nodo em questão
        a->esq = InsereArvoreABP(a->esq,ch,horas);
    else
        a->dir = InsereArvoreABP(a->dir,ch,horas); //Caso contrário, a chave é posterior, lexicograficamente, à chave do nodo em questão
    return a;
}

Nodo* ConsultaABP(Nodo *a, char ch[]) //Função extraída do enunciado do trabalho
{
    while (a != NULL)
    {
        cmpABP++;
        int comparacao = strcasecmp(a->nome, ch); //A única diferença é esta pequena otimização e mudança de função. Preferimos usar strcasecmp que faz a comparação considerando os caracteres independente de maiúsculas e minúsculas
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
int AlturaABP(Nodo *a) //Função extraída do laboratório de balanceamento de árvores binárias (não foram feitas alterações)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = AlturaABP(a->esq);
        Alt_Dir = AlturaABP(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

int ContaNodos(Nodo *a) //É uma função bem simples. Ela simplesmente sai varrendo a árvore e somando 1 ao retorno para computar o número de nodos na árvore (que corresponde à quantidade de elementos no DataSet)
{
    if(a == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + ContaNodos(a->esq) + ContaNodos(a->dir);
    }
}

int GetComparacoesABP() //Como cmpABP é uma variável global neste arquivo, utilizamos um conceito comum em Java para variáveis privadas: um Get.
{
    return cmpABP;
}

void DestroiArvoreABP(Nodo *a)  //É somente um algoritmo de destruição da árvore. Ele utiliza um caminhamento pós-fixado.
{
    if(a != NULL)
    {
        DestroiArvoreABP(a->esq);
        DestroiArvoreABP(a->dir);
        free(a);
    }
}
