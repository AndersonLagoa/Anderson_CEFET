#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int verificar_palindromo(char *string_frase, int inicio, int fim, float ponto_medio)
{
    if (inicio >= ponto_medio)
        return 1;
    else if (string_frase[inicio] != string_frase[fim])
        return 0;
    else
        return verificar_palindromo(string_frase, inicio + 1, fim - 1, ponto_medio);
}

int main()
{   char frase[100];
    char string_frase[100];

    // Recebendo a frase e colocando tudo minusculo 
    printf("\nDigite a palavra ou frase: ");
    fgets(frase, 100, stdin);
    frase[strcspn(frase, "\n")] = '\0';
    for (int i = 0; i < strlen(frase); i++)
        frase[i] = tolower(frase[i]);

    // Tirando os espaços da frase
    for (int i = 0, k = 0; i < strlen(frase); i++)
    {
        if (frase[i] != ' ')
        {
            string_frase[k] = frase[i];
            k++;
        }
    }
    // Chamando Função
    int tamanho = strlen(string_frase) - 1;
    int resultado = verificar_palindromo(string_frase, 0, tamanho, tamanho / 2);
    if (resultado == 1)
        printf("\nA frase e palindromo\n\n");
    else
        printf("\nA frase nao e palindromo\n\n");
}
