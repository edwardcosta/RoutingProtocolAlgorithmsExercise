/**
 * Função Dijkstra
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

typedef struct tabela{
    int no;
    int custo;
    struct tabela* proximo;
}tabelaDv;

void dijkstraLista(Grafo* link_state){

    int N[30];
    int i = 0;

    Grafo* link_state_aux = link_state;
    Lista_vizinho* vizinhos = NULL;
    tabelaDv* tabela = malloc(sizeof(tabelaDv));

    /*Inicializacao*/
    N[i] = link_state_aux->num; /* no raiz u */
    vizinhos = link_state_aux->vizinho; /* vizinhos de u */

    while(vizinhos != NULL){


        /*Vai para o proximo vizinho*/
        vizinhos = vizinhos->proximo;
    }
    /*Loop até N' = N*/

    /* imprimeTabela(link_state); */
}
