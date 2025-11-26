#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strNodoAVL NodoAVL;
struct strNodoAVL
{
    char nome[100]; //Armazena o título do jogo
    float horas; //Armazena as horas necessárias para concluir o jogo
    NodoAVL *dir;
    NodoAVL *esq;
    int FB; //Fator de balanceamento do nodo
};

/// Observação:
// O título do jogo, conforme o enunciado, é utilizado como chave aqui. As horas apenas são levadas junto no pacote.
// Créditos de funções que não foram implementadas pela dupla estão na .c associada.

NodoAVL* CriaArvoreAVL(); //Basicamente cria um árvore nova com raiz em NULL

NodoAVL* InsereArvoreAVL(NodoAVL *a, char x[], float tempo, int *ok); //Adiciona Nodos na ABP. Os parâmetros são: raiz da árvore, nome da chave, horas associadas e o endereço de uma variável flag para controle da altura de uma subárvore

int ContaNodosAVL(NodoAVL *a); //Retorna o número de nodos na árvore. Os parâmetros são: raiz da árvore

int AlturaAVL(NodoAVL *a); //Computa a altura da árvore e retorna esse valor. Os parâmetros são: raiz da árvore

NodoAVL* ConsultaAVL(NodoAVL *a, char ch[]); //Realiza a leitura da AVL. Os parâmetros são: raiz da árvore, nome a ser buscado

int GetRotacoesAVL(); //Retorna a variável global que armazena as rotações na .c associada

int GetComparacoesAVL(); //Retorna a variável global que armazena as comparações na .c associada

void DestroiArvoreAVL(NodoAVL *a); //Realiza free() em cada nodo por um algoritmo pós fixado. Os parâmetros são: raiz da árvore
