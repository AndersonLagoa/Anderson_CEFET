#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
   int menu;
   do
   {
    printf("----------------------------------");
    printf("\n1. Cadastrar pessoa\n2. Exibir todas as pessoas cadastradas\n3. Excluir pessoa\n4. Alterar pessoa\n5. Sair\n");
    printf("----------------------------------");
    printf("\n\nEscolhe uma opção: ");
    scanf("%d",&menu);
   } while (menu<1 || menu>5);
   
}