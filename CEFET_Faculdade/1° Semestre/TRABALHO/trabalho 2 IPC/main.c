#include "ponte.h"
int main(){
 chama_mapa();//chama o mapa do arquivo junto com o tamanho 
 confere_mapa();// confere se o mapa é de acordo com o tamanho e descobri onde estão os tesouros e o ponto inicial
 possibilidades_percorre();// quantas maneiras que chegar nos tesouros
 encontra_caminho();//encontrar os caminhos 
return 0;

 
}