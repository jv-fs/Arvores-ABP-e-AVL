# Projeto para comparação de eficiência de árvores ABP e AVL em C

## Funcionalidades:
### Inserção de dados em árvores ABP e AVL
O código realiza a inclusão em sequência de dados extraídos de um .csv em duas árvores, uma ABP e outra AVL.
### Leitura das árvores criadas por meio de uma lista de busca
Tendo as árvores criadas, o programa lê um arquivo de texto que busca pelos dados exigidos nas duas árvores, extraindo informações de eficiência.
### Retorno de performance
As informações de performance incluem: número de nodos na árvore, altura, número de rotações na inserção, número de comparações, tempo de inserção e tempo de leitura.

## Como usar:
### Opção 1: .bat
Para praticidade, o corpo do repositório possui um arquivo chamado `exec.bat`. Ele irá executar `\bin\Debug\consulta_jogos.exe` com os dados de `\bin\Debug\dataset.csv` e buscar com os títulos destacados em `\bin\Debug\lista_jogador1.txt`. A saída será entregue em `saida.txt`, no mesmo local do bat.

### Opção 2: linha de comando
Abrindo um terminal em `\bin\Debug` execute ```.\consulta_jogos.exe .\<DataBase> .\<lista> .\<resultado>``` substituindo as variáveis separadas por <> pelos paths dos arquivos que serão utilizados. Por praticidade, é recomendado colocar os arquivos dentro do diretório `\bin\Debug` e simplesmente inserir os nomes dos arquivos nos campos juntamente de sua extensão.

## Observação
Os dados do DataSet são esperados com a seguinte formatação: `Título,Horas`, linha por linha.

>Grande parte do código não é de autoria própria e os créditos estão referenciados nos `.c`. A fonte única são os PDFs disponibilizados pelos professores na plataforma da disciplina no Moodle, então os créditos estão descritos pelo número da aula ou título da atividade e página, caso necessário.
