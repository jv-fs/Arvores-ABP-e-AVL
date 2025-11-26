@echo off
title Executando Trabalho Final ED

set "PASTA_RAIZ=%~dp0"

cd "bin\Debug"

echo Executando o programa...
echo O arquivo de saida sera salvo em: %PASTA_RAIZ%saida.txt


consulta_jogos.exe dataset.csv lista_jogador1.txt "%PASTA_RAIZ%saida.txt"

echo Execucao finalizada.
pause