#include "lista.h"
void criarLista(struct ListaSimplesEnc *pList) {
 pList->primeiro = NULL;
}

void inserir_pessoas(struct ListaSimplesEnc *pList, char *nome, char *cpf){
 struct lista *novo;
 novo = (struct lista*)malloc(sizeof(struct lista));
 novo->nome = nome;
 novo->proximo = pList->primeiro;
 pList->primeiro = novo;

}
 void retirar_pessoas(){

 }
void imprimir_pessoas(){


} 
void verificar_vazio(){

}
void atendimento_prioritario(){
    
}
