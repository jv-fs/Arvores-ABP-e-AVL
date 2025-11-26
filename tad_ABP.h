#include <stdio.h>
#include <stdlib.h>

typedef struct strNodo Nodo;
struct strNodo
{
    char nome[100]; //Armazena o título do jogo
    float horas; //Armazena as horas necessárias para concluir o jogo
    Nodo *dir;
    Nodo *esq;
};

/// Observação:
// O título do jogo, conforme o enunciado, é utilizado como chave aqui. As horas apenas são levadas junto no pacote.
// Créditos de funções que não foram implementadas pela dupla estão na .c associada.

Nodo* InsereArvoreABP(Nodo *a, char ch[], float horas); //Adiciona Nodos na ABP. Os parâmetros são: raiz da árvore, nome da chave, horas associadas

Nodo* CriaArvoreABP(); //Basicamente cria um árvore nova com raiz em NULL

Nodo* ConsultaABP(Nodo *a, char ch[]); //Realiza a leitura da ABP. Os parâmetros são: raiz da árvore, nome a ser buscado

int AlturaABP(Nodo *a); //Computa a altura da árvore e retorna esse valor. Os parâmetros são: raiz da árvore

int GetComparacoesABP(); //Retorna a variável global que armazena as comparações na .c associada

int ContaNodos(Nodo *a); //Retorna o número de nodos na árvore. Os parâmetros são: raiz da árvore

void DestroiArvoreABP(Nodo *a); //Realiza free() em cada nodo por um algoritmo pós fixado. Os parâmetros são: raiz da árvore
