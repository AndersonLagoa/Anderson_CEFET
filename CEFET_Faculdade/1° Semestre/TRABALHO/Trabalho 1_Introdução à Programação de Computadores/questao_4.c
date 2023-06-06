#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int **funcao_matriz(int n) // Criar matriz, Receber os valores dos elementos e Imprimir a matriz
{
    int **matriz = (int **)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        matriz[i] = (int *)malloc(sizeof(int) * n);

    printf("\nInforme os valores os elementos 1 ou 0 (conforme exista ou não estrada direta)\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                matriz[i][j] = 1;
            else
            {
                printf("Posicao [%d][%d]: ", i + 1, j + 1);
                scanf("%d", &matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nTabela:\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", matriz[i][j]);
        printf("\n");
    }

    return matriz;
}

int *quantas_estradas_e_saidas(int **matriz, int linha, int coluna, int n, int **recebe) // Dado k, determinar quantas estradas saem e quantas chegam à cidade k.
{
    int chegam = 0, saem = 0;
    if (coluna == 1) // primeira coluna
    {
        if (matriz[linha - 1][coluna - 1] == 0)
        {
            chegam = 1;
            saem = 1;
        }
        else
        {
            if (matriz[linha][coluna] == 1)
            {
                chegam = 0;
                saem = 1;
            }
            else if (matriz[linha][coluna] == 0)
            {
                chegam = 1;
                saem = 1;
            }
        }
    }

    if (coluna == n) // ultima coluna
    {
        if (matriz[linha - 1][coluna - 1] == 0)
        {
            chegam = 2;
            saem = 2;
        }
        else
        {
            if (matriz[linha - 2][coluna - 2] == 1)
            {
                chegam = 1;
                saem = 0;
            }
            else if (matriz[linha - 2][coluna - 2] == 0)
            {
                chegam = 1;
                saem = 1;
            }
        }
    }

    else // colunas restante
    {
        if (matriz[linha - 1][coluna - 1] == 1)
        {
            if (matriz[linha - 2][coluna - 2] == 0 && matriz[linha][coluna] == 0)
            {
                chegam = 2;
                saem = 2;
            }
            else if (matriz[linha - 2][coluna - 2] == 0 && matriz[linha][coluna] == 1)
            {
                chegam = 1;
                saem = 2;
            }
            else if (matriz[linha - 2][coluna - 2] == 1 && matriz[linha][coluna] == 0)
            {
                chegam = 3;
                saem = 2;
            }
            else if (matriz[linha - 2][coluna - 2] == 1 && matriz[linha][coluna] == 1)
            {
                chegam = 1;
                saem = 1;
            }
        }
        else
        {
            chegam = 2;
            saem = 2;
        }
    }

    printf("\nDa cidade %d, existe(m) %d entrada(s) e %d saida(s)\n\n", matriz[linha-1][coluna-1], chegam, saem);


    int *recebe_re = (int *)malloc(sizeof(int) * 2);
    recebe_re[0] = chegam;
    recebe_re[1] = saem;
    *recebe = recebe_re;
    return recebe_re;
}

void maior_numero_estradas(int **matriz, int n) // A qual das cidades chega o maior número de estradas?
{
    int maior = 0, linha_maior = 0, coluna_maior = 0;
    int *aux;
    printf("O(s) maior(es) numero de estradas:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            quantas_estradas_e_saidas(matriz, i + 1, j + 1, n, &aux);
            if (maior < aux[0])
            {
                maior = aux[0];
                linha_maior = i;
                coluna_maior = j;
            }
        }
    }
    printf("Cidade[%d][%d]: %d\n",linha_maior,coluna_maior, maior);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            quantas_estradas_e_saidas(matriz, i + 1, j + 1, n,&aux);
            if (maior == aux[0])
            {
              printf("Cidade[%d][%d]: %d\n",linha_maior,coluna_maior, maior);
            }
        }
    }
    printf("\n\n");

}
void mao_dupla(int **matriz, int n, int linha, int coluna) 
{
 

}



int main()
{
    int n, questao;
    int **matriz;
    printf("Digite o tamanho da ordem da Matriz: ");
    scanf("%i", &n);

    // Criar matriz, Receber os valores dos elementos e Imprimir a matriz
    matriz = funcao_matriz(n);

    printf("\nEscolhe uma questao de 1 a 6: ");
    scanf("%i", &questao);
    switch (questao)
    {
    case 1:
    {
        int i, j, *recebe;
        recebe = (int *)malloc(sizeof(int) * 2);
        printf("\nInforme qual cidade:\n");
        printf("Posicao da linha: ");
        scanf("%d", &i);
        printf("Posicao da coluna: ");
        scanf("%d", &j);

        quantas_estradas_e_saidas(matriz, i, j, n, &recebe);

        printf("\nDa cidade %d, existe(m) %d entrada(s) e %d saida(s)\n\n", matriz[i-1][j-1], recebe[0], recebe[1]);
        break;
    }

    case 2:
    {
        maior_numero_estradas(matriz, n);
        break;
    }
    case 3:
    {
        int i, j, *recebe;
        recebe = (int *)malloc(sizeof(int) * 2);
        printf("\nInforme qual cidade:\n");
        printf("Posicao da linha: ");
        scanf("%d", &i);
        printf("Posicao da coluna: ");
        scanf("%d", &j);

        //mao_dupla(matriz, n);

        break;
    }
    case 4:
    {
    }
    case 5:
    {
    }
    case 6:
    {
    }
    default:
        exit(0);
        break;
    }
}