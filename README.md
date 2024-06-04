# Algoritmo KMP

Este repositório contém a implementação do algoritmo Knuth-Morris-Pratt (KMP).

O intento desta pesquisa é compreender e comparar dados genômicos, analisando a velocidade de processamento.

## Requisitos

Compilador C++

Python

## Exemplos

### Palavras Indeterminadas

O programa "1_Palavras_indeterminadas.py" gera palavras indeterminadas no arquivo saida.txt a partir de outros dois arquivos, neste caso 1.txt e 2.txt. 

Utilize o seguinte comando para executar o programa:

```sh
.\1_Palavras_indeterminadas.py ..\1.txt ..\2.txt ..\saida.txt
```

O arquivo de saída deve ser equivalente com o arquivo "saida.txt" que se encontra na pasta exemplos.

### Números Primos

O programa "2_num_primos.py" recebe o arquivo de saída do programa "1_Palavras_indeterminadas.py" e gera três arquivos(dois arquivos de texto e um arquivo binário) que relacionam os nucleotídeos da palavra indeterminada com números primos.

Utilize o seguinte comando para executar o programa:

```sh
.\2_num_primos.py ..\saida.txt ..\primos.bin ..\primos.txt ..\primos_decodificados.txt
```
Neste caso o arquivo "primos_decodificados.txt" deverá ser equivalente ao arquivo "primos.txt".

### Números primos para nucleotídeos

O programa "3_primos_nucleotideos.py" recebe um dos arquivos texto gerados pelo programa "2_num_primos.py" e retorna para nucleotídeos, a fim de realizar a conferência dos resultados, pois o programa deverá retornar um arquivo equivalente ao "saida.txt".

Utilize o seguinte comando para executar o programa:

```sh
.\3_primos_nucleotideos.py ..\primos.txt ..\primos_nucleotideos.txt
```

### Comparar arquivos

O programa "4_compara_arq.py" analisa se os arquivos informados são iguais.

Utilize o seguinte comando para executar o programa:

```sh
.\4_compara_arq.py ..\primos_nucleotideos.txt ..\saida.txt
```

Saída esperada:

```sh
Os tamanhos são iguais!
Os arquivos são iguais!
```




