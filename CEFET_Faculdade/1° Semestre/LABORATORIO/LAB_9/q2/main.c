#include "lista.h"
int main()
{
    struct ListaSimplesEnc minhaLista;
    //struct 
    criarLista(&minhaLista);
    int escolha;
    do
    {
        int num;
        printf("1-Inserir pessoas na lista\n2-Retirar pessoas da lista\n3-Imprimir as pessoas que estão na lista\n4-Verificar se a lista está vazia.\n5-Permitir que uma pessoa com atendimento prioritário seja atendida primeiro.\n");
        do
        {
            printf("\nEscolhe uma opção: ");
            scanf("%d", &num);
        } while (num < 1 || num > 5);
        switch (num)
        {
        case 1: // inserir
        {   char nome[40];
            char cpf[15];
            printf("Informe o nome:");
            fgets(nome,40,stdin);
            nome[strlen(nome)-1]='\0';
            printf("Informe o CPF:");
            scanf("%s",&cpf);
            inserir_pessoas(&minhaLista,nome,cpf);
            break;
        }
        case 2: // retirar
            retirar_pessoas();
            break;
        case 3: // mostrar lista
            imprimir_pessoas();
            break;
        case 4: // verificar se esta vazio
            verificar_vazio();
            break;
        case 5:
            atendimento_prioritario();
            break;
        default:
            return 0;
        }
        printf("\nAperte 1 para reiniciar ou qualquer numero para sair: ");
        scanf("%d", &escolha);

    } while (escolha == 1);
    return 0;
}