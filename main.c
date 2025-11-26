#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tad_ABP.h"
#include "tad_AVL.h"

int main(int argc, char *argv[])
{
    /// ---> Código extraído parcialmente do Exemplo de passagem de parâmetros disponibilizado no Moodle

    /// Definição dos arquivos
    FILE *entrada;
    FILE *selecao;
    FILE *saida;

    /// Definição de variáveis úteis
    clock_t start, end; //Tempo de início e fim de operações (variáveis reutilizadas para a ABP e AVL)

    // Variáveis para a leitura dos arquivos
    char linha[1000]; //Linha atual
    char *nome; //Nome do jogo
    char *horasChar; //horas do jogo, mas em string
    //

    int ok; //Check para as rotações da AVL

    /// Definição das árvores
    NodoAVL *arvoreAVL = CriaArvoreAVL(); //AVL
    NodoAVL *nodoAuxiliarAVL = NULL;

    Nodo *arvoreABP = CriaArvoreABP(); //ABP
    Nodo *nodoAuxiliar = NULL;

    /// Variáveis coletoras
    // As seguintes variáveis armazenam dados que depois vão ser exportados. Os nomes são autoexplicativos
    float totalHoras = 0;
    float totalHorasAVL = 0;

    float tempoInsercaoAVL = 0;
    float tempoInsercaoABP = 0;

    float tempoLeituraAVL = 0;
    float tempoLeituraABP = 0;

    int numeroDeNodos = 0;
    int alturaABP = 0;
    int rotacoesABP = 0;
    int comparacoesABP = 0;

    int numeroDeNodosAVL = 0;
    int alturaAVL = 0;
    int rotacoesAVL = 0;
    int comparacoesAVL = 0;


    if(argc!=4) //Essencialmente igual ao código do exemplo em vídeo, mas teremos 4 argumentos aqui (executavel.exe, dataset.csv, lista.txt, saida.txt)
    {
        printf("Número incorreto de parâmetros.\n");
        return 1;
    }

    ///  Início da implementação

    entrada = fopen(argv[1], "r"); //Abrimos o dataset.csv

    /// Inserção para ABP:
    // Exata mesma estrutura do código disponibilizado no Moodle
    ///

    if(entrada == NULL)
    {
        printf("Erro ao abrir o arquivo %s", argv[1]);
    }
    else
    {
        start = clock(); //Inicializa a contagem do tempo
        while(fgets(linha, 1000, entrada))
        {
            nome = strtok(linha, ",\n"); //Lê o nome e salva
            horasChar = strtok(NULL, "\n"); //Lê as horas e salva
            if(nome != NULL && horasChar != NULL) //É verificado se o que foi lido é válido
            {
                arvoreABP = InsereArvoreABP(arvoreABP, nome, atof(horasChar)); //Então a função de inserção é executada (a string de horas é convertida para float por meio do atof)
            }
        }
        end = clock(); //Para a contagem do tempo
        tempoInsercaoABP = (float)(end - start) / CLOCKS_PER_SEC * 1000; //Realiza a conversão do intervalo para milisegundos e salva na variável correspondente
    }
    rewind(entrada); //Como iremos utilizar o mesmo procedimento e o arquivo já está aberto, o rewind irá puxar para o início do arquivo para repetir tudo e armazenar na AVL. Essa diferença só existe por causa da contagem do tempo

    /// Inserção para AVL:
    // Praticamente o mesmo código acima
    ///
    if(entrada == NULL)
    {
        printf("Erro ao abrir o arquivo %s", argv[1]);
    }
    else
    {
        start = clock();
        while(fgets(linha, 1000, entrada))
        {
            nome = strtok(linha, ",\n");
            horasChar = strtok(NULL, "\n");
            if(nome != NULL && horasChar != NULL)
            {
                arvoreAVL = InsereArvoreAVL(arvoreAVL, nome, atof(horasChar), &ok); //A única diferença é aqui. Outro método é utilizado para a inserção, gravando os dados em uma árvore AVL. Rotações são analisadas internamente nesta função
            }
        }
        end = clock();
        tempoInsercaoAVL = (float)(end - start) / CLOCKS_PER_SEC * 1000;
    }

    fclose(entrada); //Finalizada a leitura, o arquivo de entrada pode ser fechado

    selecao = fopen(argv[2], "r"); //Abrimos o arquivo lista.txt (contendo os títulos que se quer buscar nas árvores criadas)

    /// Realiza leitura ABP
    // Novamente, mesma estrutura do código do Moodle
    ///

    if(selecao == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
    }
    else
    {
        start = clock();
        while(fgets(linha, 1000, selecao))
        {

            if(strtok(linha, "\n") != NULL) //Aqui o código extrai o texto da linha, removendo o \n, e já verifica se é válido
            {

                nodoAuxiliar = ConsultaABP(arvoreABP, linha); //Sendo válido, a ABP é consultada. Como o arquivo de leitura tem apenas os títulos, não é necessário string auxiliar

                if(nodoAuxiliar != NULL)
                {
                    totalHoras = totalHoras + nodoAuxiliar->horas; //Caso o título seja localizado na árvore, nodoAuxiliar será diferente de NULL, e o tempo armazenado pode ser computado no somatório
                }
            }
        }
        end = clock();
        tempoLeituraABP = (float)(end - start) / CLOCKS_PER_SEC * 1000;
    }

    rewind(selecao); //Mesmo esquema do arquivo de entrada. É necessário rebobinar para repetir o processo pra AVL

    /// Realiza Leitura AVL
    // Novamente, mesma estrutura do código do Moodle
    ///

    if(selecao == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
    }
    else
    {
        start = clock();
        while(fgets(linha, 1000, selecao))
        {

            if(strtok(linha, "\n") != NULL)
            {
                nodoAuxiliarAVL = ConsultaAVL(arvoreAVL, linha); //Agora a consulta é feita na AVL. Como as duas árvores são árvores de pesquisa, a função dentro das suas tads para consulta é a mesma

                if(nodoAuxiliarAVL != NULL)
                {
                    totalHorasAVL = totalHorasAVL + nodoAuxiliarAVL->horas;
                }
            }
        }
        end = clock();
        tempoLeituraAVL = (float)(end - start) / CLOCKS_PER_SEC * 1000;
    }

    fclose(selecao); //Com isso tudo feito, pode-se fechar o arquivo de seleção

    /// Computando resultados:
    //As linhas a seguir são um tanto autoexplicativas. Cada tad possui funções que desempenham a coleta dos dados exigidos no enunciado do trabalho

    //Para ABP:
    numeroDeNodos = ContaNodos(arvoreABP);
    alturaABP = AlturaABP(arvoreABP);
    comparacoesABP = GetComparacoesABP();

    //Para AVL
    numeroDeNodosAVL = ContaNodosAVL(arvoreAVL);
    alturaAVL = AlturaAVL(arvoreAVL);
    comparacoesAVL = GetComparacoesAVL();
    rotacoesAVL = GetRotacoesAVL();


    /// Exportando...

    //Com tudo pronto, basta abrir um arquivo de saída e salvar esses dados lá. Mantivemos o mesmo formato exemplo que estava no enunciado do trabalho
    saida = fopen(argv[3], "w");

    if(totalHoras != totalHorasAVL) //Esse condicional foi utilizado na fase de testes para garantir que as duas árvores desempenhavam corretamente a função. Ele não é mais necessário, mas deixamos no código
    {
        fprintf(saida, "Erro: As arvores retornaram um total de horas distinto\n");
    }
    else
    {
        fprintf(saida, "O jogador leva %.02f horas para jogar tudo\n", totalHoras);
    }


    // Impressão dos resultados no arquivo:

    fprintf(saida, "========== ESTATISTICAS ABP ==========\n");
    fprintf(saida, "Numero de Nodos: %d\n", numeroDeNodos);
    fprintf(saida, "Altura: %d\n", alturaABP);
    fprintf(saida, "Rotacoes: %d\n", rotacoesABP);
    fprintf(saida, "Comparacoes: %d\n", comparacoesABP);
    fprintf(saida, "Tempo de insercao: %f milisegundos\n", tempoInsercaoABP);
    fprintf(saida, "Tempo de leitura: %f milisegundos\n", tempoLeituraABP);

    fprintf(saida, "========== ESTATISTICAS AVL ==========\n");
    fprintf(saida, "Numero de Nodos: %d\n", numeroDeNodosAVL);
    fprintf(saida, "Altura: %d\n", alturaAVL);
    fprintf(saida, "Rotacoes: %d\n", rotacoesAVL);
    fprintf(saida, "Comparacoes: %d\n", comparacoesAVL);
    fprintf(saida, "Tempo de insercao: %f milisegundos\n", tempoInsercaoAVL);
    fprintf(saida, "Tempo de leitura: %f milisegundos\n", tempoLeituraAVL);

    //O arquivo é fechado
    fclose(saida);

    //Mesmo sabendo que o arquivo vai retornar zero e a memória vai ser liberada, mantivemos uma função de destruição das árvores por boas práticas
    DestroiArvoreABP(arvoreABP);
    DestroiArvoreAVL(arvoreAVL);

    return 0;
}
