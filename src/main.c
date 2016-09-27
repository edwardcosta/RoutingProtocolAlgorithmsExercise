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
    Grafo* link_state_djk;

    int qtd_nos = 0, qtd_trocas = 0;
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
        /**
         * Impressao do grafo da topologia lida
         */
        printf("\tGRAFO DA TOPOLOGIA LIDA: %s\n", nome_topologia);
        imprimeTabela(link_state);
        printf("\n\n");
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
                if(t != 0){
                    qtd_trocas += t;
                    troca = true;
                }
            }
        }
        printf("\tTROCAS DE TABELAS E NUMERO DE NOS NA TOPOLOGIA\n");
        printf("trocas: %d, numero de nos: %d\n", qtd_trocas, qtd_nos);
        printf("\n\n");
    }

    printf("\tALGORITMO DE DIJKSTRA\n");

    link_state_djk = link_state;

    while(link_state_djk != NULL){
        sprintf(nome_topologia, "grafo_%d", link_state_djk->num);
        link_state_aux = loadFile(nome_topologia);
        dijkstraLista(link_state_aux, qtd_nos, link_state_djk->num);
        link_state_djk = link_state_djk->proximo;
    }

    return 0;
}
