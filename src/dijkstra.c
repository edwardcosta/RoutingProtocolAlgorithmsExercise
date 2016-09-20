/**
 * Função Dijkstra
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "dijkstra.h"

typedef struct custo{
    int distancia;
    int no_anterior;
    struct custo* proximo;
}Dv;

typedef struct tabela{
    Dv* custo;
    struct tabela* proximo;
}tabelaDv;

typedef struct N{
    int no;
    struct subN* proximo;
}subN;

void dijkstraLista(Grafo* link_state, int qtd_nos){

    int i = 0;

    Grafo* link_state_aux = link_state;
    Lista_vizinho* vizinhos = NULL;
    tabelaDv* tabela_custo = malloc(sizeof(tabelaDv));
    subN* N = malloc(sizeof(subN));

    /*Inicializacao*/
    link_state_aux = link_state;
    N->no = link_state_aux->num; /* no raiz u */
    N->proximo = NULL;
    vizinhos = link_state_aux->vizinho; /* vizinhos de u */

    /*Para todos vizinhos do no raiz na tabela de custo*/
    while(vizinhos != NULL){
        if(ehVizinho(vizinhos->vizinho, link_state_aux)){
            tabela_custo->custo->distancia = vizinhos->custo;
            tabela_custo->custo->no_anterior = vizinhos->vizinho;
            printf("eh vizinho: %d -> %d", link_state_aux->num, vizinhos->vizinho);
        }else{
            tabela_custo->custo->distancia = -1;
        }
        /*Vai para o proximo vizinho*/
        vizinhos = vizinhos->proximo;
    }
    /*Loop até N' = N*/

    /* imprimeTabela(link_state); */
    return;
}

int ehVizinho(int vizinho, Grafo* link_state){
    Grafo* link_state_aux = link_state;
    while(link_state_aux != NULL){
        if(vizinho == link_state_aux->num){
            return 1;
        }
        link_state_aux = link_state_aux->proximo;
    }
    return 0;
}
