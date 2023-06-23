#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lista {
     char nome[40];
     char pdf[15];
     struct lista *proximo;
};

struct ListaSimplesEnc {
 struct lista *primeiro;
};
void criarLista(struct ListaSimplesEnc *pList);
void inserir_pessoas(struct ListaSimplesEnc *pList, char *nome, char *cpf);
int retirar_pessoas();
int imprimir_pessoas();
int verificar_vazio();
int atendimento_prioritario();
#endif