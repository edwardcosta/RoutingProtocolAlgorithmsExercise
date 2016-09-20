/**
* Função Dijkstra
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "dijkstra.h"

void dijkstraLista(Grafo* link_state, int qtd_nos, int raiz){

    Grafo* link_state_aux = link_state;

    Lista_vizinho* vizinhos = NULL;

    subN* N = NULL;

    tabelaDv* tabela_custo = NULL;
    tabelaDv* tabela_custo_aux = NULL;

    Dv* custo_aux = NULL;
    Dv* custo = NULL;

    /*Inicializacao*/
    printf("no raiz: %d\n", raiz);
    link_state_aux = link_state;
    N->no = raiz; /* no raiz u */
    N->proximo = NULL;
    vizinhos = link_state_aux->vizinho; /* vizinhos de u */

    /*Para todos vizinhos do no raiz na tabela de custo*/
    while(link_state_aux != NULL){
        if(link_state_aux->num == N->no){
            if(link_state_aux->proximo == NULL){
                break;
            }else{
                link_state_aux = link_state_aux->proximo;
            }
        }
        custo_aux = NULL;
        custo = NULL;
        if(ehVizinho(vizinhos->vizinho, link_state_aux)){
            custo_aux = calloc(1, sizeof(Dv));
            custo_aux->distancia = vizinhos->custo;
            custo_aux->no_anterior = vizinhos->vizinho;
            custo_aux->proximo = custo;
            custo = custo_aux;

            printf("eh vizinho: %d\n", custo->no_anterior);

            if(vizinhos->proximo != NULL){
                vizinhos = vizinhos->proximo;
            }
        }else{
            custo_aux = calloc(1, sizeof(Dv));
            custo_aux->distancia = -1;
            custo_aux->no_anterior = link_state_aux->num;
            custo_aux->proximo = custo;
            custo = custo_aux;

            printf("nao vizinho: %d\n", custo->no_anterior);

        }
        tabela_custo_aux->custo = custo;
        tabela_custo_aux->custo->proximo = tabela_custo->custo;
        tabela_custo->custo = tabela_custo_aux->custo;
        /*Vai para o proximo vizinho*/
        link_state_aux = link_state_aux->proximo;
    }
    imprimeTabelaCusto(tabela_custo->custo);

    /*Loop até N' = N*/
    while(!completo(N)){
        /**
        * Encontrar no w nao existente em N
        * tal que D(w) eh um minimo
        */


        /**
        * Adicione w ao subconjunto N
        */


        /**
        * Atualize os custo para cada vizinho(v) de w e nao
        * em N:
        *     D(v) = minimo(D(v), D(w)+c(w, v))
        */


    }
    return;
}

int ehVizinho(int vizinho, Grafo* link_state){
    if(vizinho == link_state->num){
        return 1;
    }
    return 0;
}

void imprimeTabelaCusto(Dv* custo){
    Dv* aux = custo;
    /**
    * percorre tabela
    */
    for(; aux != NULL; aux = aux->proximo){
        printf("vizinho: %d\n", aux->no_anterior);
        printf("custo: %d\n", aux->distancia);
    }
    return;
}

int completo(subN* N){

return 0;
}
