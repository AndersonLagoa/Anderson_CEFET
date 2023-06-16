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

void operacao(int *numeros, int quantidade)
{
    // Leia os números do arquivo binário e calcule a soma, a média e a quantidade deles
    float soma = 0;
    float media;
    for (int i = 0; i < quantidade; i++)
        soma += numeros[i];

    media = soma / (quantidade*1.00);
    
    printf("%d\n\n\n\n\n",quantidade);
    float text_resultado_write[3];
    text_resultado_write[0] = soma;
    text_resultado_write[1] = media;
    text_resultado_write[2] = quantidade;
    float text_resultado_read[3];

   for (int i = 0; i < quantidade; i++)
       printf("%d ",numeros[i]);
    printf("\n\n%f\t%f\n\n", text_resultado_write[0], media, text_resultado_write[2]);// ate aqui esta funcionando

    FILE *arquivo;
    if (fopen("resultadoTotal.bin", "rb") == NULL)
    {
        arquivo = fopen("resultadoTotal.bin", "wb");
        fwrite(text_resultado_write, sizeof(float), 3, arquivo);
        fclose(arquivo);
    }
    else
    {
        arquivo = fopen("resultadoTotal.bin", "ab");
        fwrite(text_resultado_write, sizeof(float), 3, arquivo);
        fclose(arquivo);
    }

    arquivo = fopen("resultadoTotal.bin", "rb");
    fseek(arquivo, sizeof(int), SEEK_SET);
    if (arquivo != NULL)
    {
        while (1)
        {
            fread(text_resultado_read, sizeof(float), 3, arquivo);
            if (feof(arquivo))
                break;
            printf("NOME Soma: %.2f  Media: %.2f  Quantidade: %.2f\n",text_resultado_read[2], text_resultado_read[1],text_resultado_read[0]);
            
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

    operacao(cpy_numeros,tam);
}