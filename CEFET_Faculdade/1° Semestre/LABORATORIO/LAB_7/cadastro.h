#ifndef CADASTRO_H
#define CADASTRO_H

typedef struct cad {
    char nome[50];
    char endereco[60];
    char telefone[15];
    int idade;
    char CPF[11];
}Cadastro[100];


void novo_cadastro(int i);
void exibir_cadastro();
void excluir_cadastro();
void alterar_cadastro();
void sair_cadastro();

#endif 