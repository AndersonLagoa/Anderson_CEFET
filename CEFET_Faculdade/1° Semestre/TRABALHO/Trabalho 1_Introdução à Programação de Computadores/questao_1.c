#include <stdio.h>
#include <stdlib.h>

// Dimensão da Matriz
#define linhas 23
#define colunas 23
// Ponto de inicio
#define inicio_linha 2
#define inicio_coluna 2
// Ponto de Final
#define final_linha 20
#define final_coluna 19

// Definir quantidade maxima de passos, para encerrar o programa caso não ache
// um caminho
#define passos_max 200

// Labirinto
int labirinto[linhas][colunas] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// declarando inteiros para andar no labirinto;
int l = inicio_linha;
int c = inicio_coluna;
int esquerda, direita, baixo, cima;
int passos = 0;

// Função para imprimir o labirinto
void imprimir_labirinto() {
  int i, j;
  char c;
  // Percorrer o labirinto
  for (i = 0; i < linhas; i++) {
    for (j = 0; j < colunas; j++) {
      // Determinando o inicio como S
      if (i == inicio_linha && j == inicio_coluna) {
        c = 'S';
        // Determinando o final como F
      } else if (i == final_linha && j == final_coluna) {
        c = 'F';
      } else {
        // Substituindo cada número por seu respectivo caracter
        if (labirinto[i][j] == 0) {
          c = ' ';
        } else if (labirinto[i][j] == 1) {
          c = '#';
        } else if (labirinto[i][j] == 2) {
          c = '.';
        }
        // Outro . no número 3 para o programa não voltar em caminhos que já
        // passou
        else if (labirinto[i][j] == 3) {
          c = '.';
        } else {
          c = ' ';
        }
      }
      // Imprimindo
      printf(" %c", c);
    }
    printf("\n");
  }
}

// Função para andar por todo o labirinto
void andar_labirinto() {
  esquerda = labirinto[l][c - 1];
  direita = labirinto[l][c + 1];
  cima = labirinto[l - 1][c];
  baixo = labirinto[l + 1][c];
  // Verificando se tem " " em todas as direções da posição
  if (baixo == 0) {
    l++;
    labirinto[l][c] = 2;
    passos++;
  } else if (direita == 0) {
    c++;
    labirinto[l][c] = 2;
    passos++;
  } else if (cima == 0) {
    l--;
    labirinto[l][c] = 2;
    passos++;
  } else if (esquerda == 0) {
    c--;
    labirinto[l][c] = 2;
    passos++;
  }
  // Garantir que se ele precisar voltar não percorra o mesmo caminho
  // posteriormente, por isso a antiga posição passa a valer 3
  else if (baixo == 2) {
    l++;
    labirinto[l][c] = 2;
    labirinto[l - 1][c] = 3;
    passos++;
  } else if (direita == 2) {
    c++;
    labirinto[l][c] = 2;
    labirinto[l][c - 1] = 3;
    passos++;
  } else if (cima == 2) {
    l--;
    labirinto[l][c] = 2;
    labirinto[l + 1][c] = 3;
    passos++;
  } else if (esquerda == 2) {
    c--;
    labirinto[l][c] = 2;
    labirinto[l][c + 1] = 3;
    passos++;
  }
  // Caso o programa ficar em loop até uma quantidade maxima de passos, o
  // programa se encerra e informa que não foi possível encontrar um caminho
  if (passos == passos_max) {
    printf("--------------- CAMINHO NÃO ENCONTRADO! ----------------");
    imprimir_labirinto();
    exit(0);
  }
}

void encontrar_caminho() {
  // Fazendo o labirinto andar até chegar no ponto de chegada
  while (l != final_linha || c != final_coluna) {
    andar_labirinto();
  }
}

int main(void) {
  //Chamando a função que encontra o caminho do labirinto
  encontrar_caminho();
  //Se tiver chegado até aqui, um caminho foi encontrado, portanto imprime-se uma mensagem informando isso
  printf("\n ----------- CAMINHO ENCONTRADO!! -----------\n");
  //imprimindo o labirinto com o caminho já encontrado
  imprimir_labirinto();
  printf("\n --------------- FIM DE JOGO ---------------");

  return 0;
}