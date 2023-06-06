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

int quantas_estradas_e_saidas(int **matriz, int k, int n, int **transfere) // Dado k, determinar quantas estradas saem e quantas chegam à cidade k.
{
    int chegam = 0, saem = 0;

    for (int i = 0; i < n; i++)
    {
        if (matriz[k - 1][i] == 1)
            saem++;
        if (matriz[i][k - 1] == 1)
            chegam++;
    }

    int recebe[2];
    recebe[0] = chegam - 1;
    recebe[1] = saem - 1;
    *transfere = recebe;
    return *recebe;
}

void maior_numero_estradas(int **matriz, int n) // A qual das cidades chega o maior número de estradas?
{
    int maior = -1, cidade = 0, compara = 0, recebe = 0;
    ;
    int *aux;
    printf("O(s) maior(es) numero de estradas:\n");

    for (int i = 0; i < n; i++)
    {
        quantas_estradas_e_saidas(matriz, i + 1, n, &aux);
        recebe = aux[0];
        if (maior < recebe)
        {
            maior = recebe;
            cidade = i;
        }
    }
    printf("Cidade %d: %d\n", cidade + 1, maior);
    for (int i = 0; i < n; i++)
    {
        quantas_estradas_e_saidas(matriz, i + 1, n, &aux);
        recebe = aux[0];
        if (cidade != i)
            if (maior == recebe)
                printf("Cidade %d: %d\n", i + 1, maior);
    }
    printf("\n\n");
}

void mao_dupla(int **matriz, int n, int k) // Verifica se todas as ligações com uma cidade são de mão dupla!
{
    int aux = 0;

    for (int i = 0; i < n; i++)
        if (k - 1 != i)
        {
            if (matriz[k - 1][i] == 1 && matriz[i][k - 1] == 1)
                aux = 1;
            else
                aux = 0;
        }

    //
    if (aux == 1)
        printf("\nTodas as ligações são de mão dupla");
    else if (aux == 0)
        printf("\nNem todas as ligações são de mão dupla");
}

void saidas_diretas_para_k(int **matriz, int n, int k)
{
    int *cidades = (int *)malloc(sizeof(int) * n);
    int costante = 0;

    for (int i = 0; i < n; i++)
        if (k - 1 != i)
            if (matriz[i][k - 1] == 1)
            {
                cidades[costante] = i + 1;
                costante++;
            }

    printf("Cidades que tem saída direto para %d:\n", k);
    for (int i = 0; i < costante; i++)
        printf("%d, ", cidades[i]);
    printf("\b\b.");
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
        int k;
        int *recebe = (int *)malloc(sizeof(int) * 2);
        printf("\nInforme qual cidade:\n");
        scanf("%d", &k);

        quantas_estradas_e_saidas(matriz, k, n, &recebe);

        printf("\nDa cidade %d, existe(m) %d entrada(s) e %d saida(s)\n\n", k, recebe[0], recebe[1]);
        break;
    }

    case 2:
    {
        maior_numero_estradas(matriz, n);
        
        break;
    }
    case 3:
    {
        int k;
        printf("\nInforme qual cidade: ");
        scanf("%d", &k);

        mao_dupla(matriz, n, k);

        break;
    }
    case 4:
    {
        int k;
        printf("Informe qual cidade: ");
        scanf("%d", &k);
        saidas_diretas_para_k(matriz, n, k);
        break;
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