#include "encontra.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int **distancia(int **matriz, int cost, int linha, int coluna)
{
    // printf("\nrodou uma vez\n\n");
    for (int i = 1; i < linha - 1; i++)
        for (int j = 1; j < coluna - 1; j++)
        {
            if (matriz[i][j] > 0)
            {
                if (matriz[i - 1][j] > matriz[i][j] + 1)
                    matriz[i - 1][j] = matriz[i][j] + 1;

                if (matriz[i + 1][j] > matriz[i][j] + 1)
                    matriz[i + 1][j] = matriz[i][j] + 1;

                if (matriz[i][j - 1] > matriz[i][j] + 1)
                    matriz[i][j - 1] = matriz[i][j] + 1;

                if (matriz[i][j + 1] > matriz[i][j] + 1)
                    matriz[i][j + 1] = matriz[i][j] + 1;
            }
        }

    if (cost == 0)
        return matriz;
    else
        return distancia(matriz, cost - 1, linha, coluna);
}

int **vericar_tesouros(char **mapa_mod, int **mapa_trocado, int **mapa_ver, int linha, int coluna, int *tesouro) // verificar se todos os tesouros é possivel pegar e pegar as posições dos tesouros
{
    int **matriz_distancia = (int **)malloc(sizeof(int *) * 30);
    for (int i = 0; i < 30; i++)
        matriz_distancia[i] = (int *)malloc(sizeof(int) * 3);

    int *vetor_menor = (int *)mallloc(sizeof(int *) * 4);

    vetor_menor[0] = 0;
    vetor_menor[1] = 0;
    vetor_menor[2] = 0;
    vetor_menor[3] = 0;

    int tesouroPosivel = 0;

    int menor = 1000;
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (mapa_mod[i][j] == '!')
            {

                if (mapa_trocado[i + 1][j] != 0 || mapa_trocado[i + 1][j] != 1000) // lado esquedo
                    vetor_menor[0] = mapa_trocado[i + 1][j];

                if (mapa_trocado[i + 1][j + 2] != 0 || mapa_trocado[i + 1][j + 2] != 1000) // lado direito
                    vetor_menor[1] = mapa_trocado[i + 1][j + 2];

                if (mapa_trocado[i][j + 1] != 0 || mapa_trocado[i][j + 1] != 1000) // para cima
                    vetor_menor[2] = mapa_trocado[i][j + 1];

                if (mapa_trocado[i + 2][j + 1] != 0 || mapa_trocado[i + 2][j + 1] != 1000) // para baixo
                    vetor_menor[3] = mapa_trocado[i + 2][j + 1];

                int cost = 0;
                for (int i = 0; i < 4; i++)
                    if (vetor_menor[i] != 0)
                        cost++;

                if (cost != 0)
                {

                    for (int i = 0; i < 4; i++)
                        if (vetor_menor[i] < menor)
                            menor = vetor_menor[i];

                    matriz_distancia[tesouroPosivel][0] = i;
                    matriz_distancia[tesouroPosivel][1] = j;
                    matriz_distancia[tesouroPosivel][2] = menor;
                    tesouroPosivel++;
                }
            }
        }
    }

    if (tesouroPosivel == 0)
    {
        printf("Nao e possivel buscar os tesouros!!\n\n");
        exit(0);
    }

    *tesouro = tesouroPosivel;
    return matriz_distancia;
}

void principal_concontra(char **mapa, char **mapa_mod, int **mapa_trocado, int *posicao_Inicial, int linha, int coluna, int tesouro)
{
    int **valorDistancia_inicial, **matriz_ver = (int **)mallloc(sizeof(int *) * (linha + 2));
    for (int i = 0; i < (linha + 2); i++)
        matriz_ver[i] = (int *)malloc(sizeof(int) * (coluna + 2));

    matriz_ver = distancia(mapa_trocado, tesouro, linha, coluna);

    valorDistancia_inicial = vericar_tesouro(mapa_mod, mapa_trocado, matriz_ver, linha, coluna, &tesouro);

    for (int i = 0; i < tesouro; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ",valorDistancia_inicial[i][j]);
        }
        printf("\n");
    }
}