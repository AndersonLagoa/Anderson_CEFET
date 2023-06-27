#include "central.h"
char *chama_mapa(){
int linha, coluna;
FILE *arquivo = fopen("mapa.txt","r");
If(arquivo==NULL){
printf("Erro em abrir o arquivo mapa!!\n\n");
exit(0);
}
fscanf(arquivo, "%d","%d",linha, coluna);
char **mapa = (char **)malloc(linha*sizeof(int *);
fordaW4