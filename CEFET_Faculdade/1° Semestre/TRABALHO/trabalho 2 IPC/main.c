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

void vericar_tesouro(char **mapa_mod, int **mapa_ver, int linha, int coluna, int *tesouro,int ***alorDistancia_inicial) // verificar se todos os tesouros é possivel pegar e pegar as posições dos tesouros
{

    printf("chegou em vericiar tesouro\n\n");
    int **matriz_distancia = (int **)malloc(sizeof(int *) * 30);
    for (int i = 0; i < 30; i++)
        matriz_distancia[i] = (int *)malloc(sizeof(int) * 3);

    int *vetor_menor = (int *)malloc(sizeof(int) * 4);
    // int vetor_menor[4];

    vetor_menor[0] = 0;
    vetor_menor[1] = 0;
    vetor_menor[2] = 0;
    vetor_menor[3] = 0;

    int tesouroPosivel = 0;

    int menor;
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (mapa_mod[i][j] == '!')
            {
                   printf("caio:%d %d\n\n",i,j);
                if (mapa_ver[i + 1][j] != 0 || mapa_ver[i + 1][j] != 1000) // lado esquedo
                    vetor_menor[0] = mapa_ver[i + 1][j];

                if (mapa_ver[i + 1][j + 2] != 0 || mapa_ver[i + 1][j + 2] != 1000) // lado direito
                    vetor_menor[1] = mapa_ver[i + 1][j + 2];

                if (mapa_ver[i][j + 1] != 0 || mapa_ver[i][j + 1] != 1000) // para cima
                    vetor_menor[2] = mapa_ver[i][j + 1];

                if (mapa_ver[i + 2][j + 1] != 0 || mapa_ver[i + 2][j + 1] != 1000) // para baixo
                    vetor_menor[3] = mapa_ver[i + 2][j + 1];

                int cost = 0;
                for (int i = 0; i < 4; i++)
                    if (vetor_menor[i] != 0)
                        cost++;

                if (cost != 0)
                {
                    menor = 1000;
                    for (int i = 0; i < 4; i++)
                        if (vetor_menor[i] < menor && vetor_menor[i] !=0 )
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
    printf("saiu em vericiar tesouro\n\n");
    *alorDistancia_inicial= matriz_distancia;
}

/*void principal_concontra(char **mapa, char **mapa_mod, int **mapa_trocado, int *posicao_Inicial, int linha, int coluna, int tesouro)
{
    int **valorDistancia_inicial;


    int **matriz_ver = (int **)mallloc(sizeof(int) * (linha + 2));
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
*/

void ler_mapa(char ***mapa, int *linha, int *coluna)
{
    int linha_mapa, coluna_mapa;
    FILE *arquivo = fopen("mapa.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro em abrir o arquivo mapa!!\n\n");
        exit(0);
    }
    fscanf(arquivo, "%d %d", &linha_mapa, &coluna_mapa); // ler os numeros

    char **le_mapa = (char **)malloc(sizeof(int *) * linha_mapa);
    for (int i = 0; i < linha_mapa; i++)
        le_mapa[i] = (char *)malloc(sizeof(int) * coluna_mapa);

    for (int i = 0; !feof(arquivo); i++) // ler o mapa
        fscanf(arquivo, "%s", le_mapa[i]);

    fclose(arquivo);
    *mapa = le_mapa;
    *linha = linha_mapa;
    *coluna = coluna_mapa;
}

void verificar_mapa(char **mapa, int linha, int coluna, int **posicao, char ***novoMapa, int *Qtesouro)
{
    char **mapa_novo = (char **)malloc(sizeof(int *) * linha);
    for (int i = 0; i < linha; i++)
        mapa_novo[i] = (char *)malloc(sizeof(int) * coluna);

    for (int i = 0; i < linha; i++)
        for (int j = 0; j < coluna; j++)
            mapa_novo[i][j] = mapa[i][j];

    int tesouro = 0;
    int *posicao_comeca = (int *)malloc(sizeof(int) * 2);

    for (int i = 0; i < linha; i++) // limitar os espaços em volta dos canibaias
    {
        for (int j = 0; j < coluna; j++)
        {
            if (mapa[i][j] == '*')
            {
                mapa_novo[i][j - 1] = '#';     // lado esquerdo
                mapa_novo[i][j + 1] = '#';     // lado direito
                mapa_novo[i - 1][j] = '#';     // encima
                mapa_novo[i + 1][j] = '#';     // embaixo
                mapa_novo[i - 1][j - 1] = '#'; // quina superior esquerdo
                mapa_novo[i - 1][j + 1] = '#'; // quina superior direiro
                mapa_novo[i + 1][j - 1] = '#'; // quina inferior esquerdo
                mapa_novo[i + 1][j + 1] = '#'; // quina inferior direito
            }
        }
    }

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (mapa_novo[i][j] == '!') // quantidades de tesouros e suas localizações
                tesouro++;
            if (mapa_novo[i][j] == '@') // pegar a localização inicial
            {
                posicao_comeca[0] = i + 1;
                posicao_comeca[1] = j + 1;
            }
        }
    }

    *novoMapa = mapa_novo;
    *posicao = posicao_comeca;
    *Qtesouro = tesouro;
}

void trocar_mapa(char **mapa_mod, int linha, int coluna, int *posicao, int ***matriz_tr)
{

    int **mapa_trocado = (int **)malloc(sizeof(int *) * (linha + 2));
    for (int i = 0; i < (linha + 2); i++)
        mapa_trocado[i] = (int *)malloc(sizeof(int) * (coluna + 2));

    for (int i = 0; i < (linha + 2); i++)
        for (int j = 0; j < (coluna + 2); j++)
        {
            if (i == 0 || j == 0 || i == (linha + 1) || j == (coluna + 1)) // parede
                mapa_trocado[i][j] = 0;
            else
            {
                if (mapa_mod[i - 1][j - 1] == '#' || mapa_mod[i - 1][j - 1] == '*' || mapa_mod[i - 1][j - 1] == '~') // trocagem no mapa
                    mapa_trocado[i][j] = 0;
                else
                    mapa_trocado[i][j] = 1000;
            }
        }

    mapa_trocado[posicao[0]][posicao[1]] = 1;
    *matriz_tr = mapa_trocado;
}
int main()
{
    char **mapa, **mapa_mod;
    int *posicao_Inicial;
    int linha, coluna, tesouro;
    ler_mapa(&mapa, &linha, &coluna);

    printf("--------------MAPA--------------\n\n");
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
            printf("%c ", mapa[i][j]);
        printf("\n");
    }
    printf("\n");

    verificar_mapa(mapa, linha, coluna, &posicao_Inicial, &mapa_mod, &tesouro);

    printf("--------------MAPA mod----------\n\n");
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
            printf("%c ", mapa_mod[i][j]);
        printf("\n");
    }
    printf("\n");

    int **mapa_trocado;
    trocar_mapa(mapa_mod, linha, coluna, posicao_Inicial, &mapa_trocado);

    printf("--------------MAPA trocado-------\n\n");
    for (int i = 0; i < linha + 2; i++)
    {
        for (int j = 0; j < coluna + 2; j++)
            printf("%i ", mapa_trocado[i][j]);
        printf("\n");
    }
    printf("\n");

    // principal_concontra(mapa,mapa_mod,mapa_trocado,posicao_Inicial,linha,coluna,tesouro);
    int cost = 0;
    for (int i = 0; i < (linha + 2); i++)
        for (int j = 0; j < (coluna + 2); j++)
            if (mapa_trocado[i][j] == 1000)
            {
                cost++;
            }
    printf("%d\n\n", cost);
    int **valorDistancia_inicial;

    int **matriz_ver = (int **)malloc(sizeof(int *) * (linha + 2));
    for (int i = 0; i < (linha + 2); i++)
        matriz_ver[i] = (int *)malloc(sizeof(int) * (coluna + 2));

    matriz_ver = distancia(mapa_trocado, cost, linha, coluna);
    for (int i = 0; i < linha + 2; i++)
    {
        for (int j = 0; j < coluna + 2; j++)
        {
            printf("%d ", matriz_ver[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    vericar_tesouro(mapa_mod, matriz_ver, linha, coluna, &tesouro,&valorDistancia_inicial);

    for (int i = 0; i < tesouro; i++)
     {
        for (int j = 0; j < 3; j++)
         {
             printf("%d ",valorDistancia_inicial[i][j]);
         }

     }   
}
