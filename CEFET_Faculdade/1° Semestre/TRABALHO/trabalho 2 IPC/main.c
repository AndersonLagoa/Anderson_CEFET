#include "encontra.h"

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
    int posicao_comeca[2];

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
            if (mapa_novo[i][j] == '!')
                tesouro++;
            if (mapa_novo[i][j] == '@')
            {
                posicao_comeca[0] = i +1;
                posicao_comeca[1] = j +1;
            }
        }
    }

    *novoMapa = mapa_novo;
    *posicao = posicao_comeca;
    *Qtesouro = tesouro;
    
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

    verificar_mapa(mapa, linha, coluna, &posicao_Inicial, &mapa_mod,&tesouro);
    printf("%d %d",posicao_Inicial[0],posicao_Inicial[1]);

    principal(mapa,mapa_mod,posicao_Inicial,linha,coluna,tesouro);
    
}
