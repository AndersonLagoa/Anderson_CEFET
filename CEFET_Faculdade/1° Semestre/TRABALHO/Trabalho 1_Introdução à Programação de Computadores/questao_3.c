#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int verificar_palindromo(char *frase, int inicial, int final)
{
}
int main()
{ // Recebendo a frase e colocando tudo minusculo
    char frase[100];
    printf("\nDigite a palavra ou frase: ");
    fgets(frase, 100, stdin);
    frase[strcspn(frase, "\n")] = '\0';
    for (int i = 0; i < strlen(frase); i++)
        frase[i] = tolower(frase[i]);

    // Tirando os espaços da frase
    char string_frase[100];
    int k = 0;

    for (int i = 0; i < strlen(frase); i++)
    {
        if (frase[i] != ' ')
        {
            strcat(string_frase, frase[i]);
            k++;
        }
        printf("teste");
    }
}
