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
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "file.h"
#include "dijkstra.h"

int main(int argc, char **argv) {

    Grafo* link_state;
    Grafo* link_state_aux;

    int troca = true;
    int numTrocas = 0;

    if(argc != 2){

        printf("\nERROR: numero de argumentos de entrada inválido\n");
        printf("formato entrada: ./main nome_topologia\n");
    }else{
        char nome_topologia[20];
        strcpy(nome_topologia, argv[1]);
        /**
         * Recebe o nome da topologia por linha de comando e a partir do arquivo
         * eh gerado um grafo com os dados lidos, nos, vizinhos e custos
         */
        link_state = loadFile(nome_topologia);
        /*imprimeTabela(link_state);*/
        /**
         * Faz troca de dados enquanto ha troca de dados dos nos entre os nos
         */
        while(troca == true){
            troca = false;
            link_state_aux = link_state;
            while(link_state_aux != NULL){
                int t = escreveTabelaTopologia(link_state_aux);
                link_state_aux = link_state_aux->proximo;
                numTrocas += t;
                if(t != 0){
                    troca = true;
                }
            }
        }
        imprimeTabelaGrafo();
    }
    dijkstraLista(link_state);
    return 0;
}
