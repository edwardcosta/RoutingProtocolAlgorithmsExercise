/**********************************************************************
*                      UNIVERSIDADE DE BRASILIA
*                              2/2016
*                     Teleinforamtica e redes 2
*            Eduardo Calandrini Rocha da Costa 	- 13/0059595
*            Douglas Shiro Yokoyama				- 13/0024902
**********************************************************************
** Algoritmo de roteamento Link State
* Programa que visa a simulação do algoritmo de roteamento Link State
* utilizando o algoritmo de Dijkstra para cálculo de menor caminho
*
** Entrada:
*      arquivo .txt com informações sobre a topologia de uma rede
*      no formato:
*          nodo; vizinho1[custo]; vizinho2[custo]; · · · , vizinhoN[custo]
** Saida:
*      Lista de destino e custos;
*      Convergência;
*      Validação.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int main(int argc, char **argv) {

    Grafo* link_state;
    Grafo* link_state_aux;

    int troca = 1;

    if(argc != 2){
        printf("\nERROR: numero de argumentos de entrada inválido\n");
        printf("formato entrada: ./main nome_topologia\n");
    }else{
        char nome_topologia[20];
        strcpy(nome_topologia, argv[1]);
        link_state = loadFile(nome_topologia);
        //imprimeTabela(link_state);
        while(troca){
            link_state_aux = link_state;
            while(link_state_aux != NULL){
                troca = escreveTabelaTopologia(link_state);
                link_state_aux = link_state_aux->proximo;
            }
        }
        imprimeTabelaGrafo();
    }
    return 0;
}
