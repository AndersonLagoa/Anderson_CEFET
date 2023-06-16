#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int *gerado_numeros(int tam)
{
    int *vetor;
    vetor = (int *)malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++)
        vetor[i] = (rand() % 18) + 2;

    return vetor;
}
int *ler_numeros(char *nome, int tam)
{
    FILE *arquivo = fopen(nome, "rb");
    if (arquivo == NULL)
    {
        printf("ERRO! Não foi possivel abrir o arquivo.");
        exit(0);
    }
    int *numeros = (int *)malloc(tam * sizeof(int));
    fread(numeros, sizeof(int), 50, arquivo);
    fclose(arquivo);
    return numeros;
}

void operacao(int *numeros)
{
    // Leia os números do arquivo binário e calcule a soma, a média e a quantidade deles
    int soma = 0, media, quantidade = sizeof(numeros) + 1;
    for (int i = 0; i < quantidade; i++)
        soma += numeros[i];
    media = soma / quantidade;

    int text_resultado_write[]= {soma, media, quantidade};
    int text_resultado_read[3];

    printf("\n\n%d\t%d\n\n", soma, media);// ate aqui esta funcionando

    FILE *arquivo = fopen("resultadoTotal.bin", "rb");
    if (arquivo == NULL)
    {
        fclose(arquivo);

        arquivo = fopen("resultadoTotal.bin", "wb");
        fwrite(text_resultado_write, sizeof(int), 3, arquivo);
        fclose(arquivo);
    }
    else
    {
        fclose(arquivo);

        arquivo = fopen("resultadoTotal.bin", "ab");
        fwrite(text_resultado_write, sizeof(int), 3, arquivo);
        fclose(arquivo);
    }

    arquivo = fopen("resultadoTotal.bin", "rb");
    fseek(arquivo, sizeof(int), SEEK_SET);
    if (arquivo != NULL)
    {
        while (1)
        {
            fread(text_resultado_read, sizeof(int), 3, arquivo);
            if (feof(arquivo))
                break;
            printf("NOME Soma: %d  Media: %d  Quantidade: %d\n",text_resultado_read[0], text_resultado_read[1],text_resultado_read[2]);
            
        }
    }
    fclose(arquivo);
}
int main()
{
    int *numeros, *cpy_numeros, tam;
    char nome[15];
    printf("Informe a quantidade de numeros para ser gerados: ");
    scanf("%d", &tam);

    numeros = gerado_numeros(tam);

    printf("Informe o nome para o arquivo binario: ");
    fflush(stdin);
    fgets(nome, 15, stdin);
    nome[strlen(nome) - 1] = '\0';
    strcat(nome, ".bin");

    FILE *arquivo = fopen(nome, "wb");
    if (arquivo == NULL)
    {
        printf("ERRO! Não foi possivel criar o arquivo.");
        exit(0);
    }
    fwrite(numeros, sizeof(int), tam, arquivo);
    fclose(arquivo);

    cpy_numeros = ler_numeros(nome, tam);

    operacao(cpy_numeros);
}