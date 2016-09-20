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

    int i, qtd_nos = 0, qtd_trocas = 0;
    int troca = true;

    char nome_topologia[20];

    if(argc != 2){

        printf("\nERROR: numero de argumentos de entrada inválido\n");
        printf("formato entrada: ./main nome_topologia\n");
    }else{
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
            qtd_nos = 0;
            while(link_state_aux != NULL){
                int t = escreveTabelaTopologia(link_state_aux);
                qtd_nos++;
                link_state_aux = link_state_aux->proximo;
                if(t == true){
                    qtd_trocas++;
                    troca = true;
                }
            }
        }
        printf("trocas: %d, numero de nos: %d\n", qtd_trocas, qtd_nos);
    }

    for(i = 1; i <= qtd_nos; i++){
        sprintf(nome_topologia, "grafo_%d", i);
        link_state_aux = loadFile(nome_topologia);
        /*dijkstraLista(link_state_aux, qtd_nos);*/
    }

    imprimeTabela(link_state);
    dijkstraLista(link_state_aux, qtd_nos);
    return 0;
}
