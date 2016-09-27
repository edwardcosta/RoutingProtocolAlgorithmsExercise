/**
* Função Dijkstra
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grafo.h"
#include "dijkstra.h"
#include "file.h"

/**
 * [dijkstraLista calculo das menores distancias para todos os nos da
 * topologia]
 * @param link_state [Grafo lido da topologia]
 * @param qtd_nos    [quantidade de nos na topologia lida]
 * @param raiz       [No relação para o calculo das distancias]
 */
void dijkstraLista(Grafo* link_state, int qtd_nos, int raiz){

    listaDist *dist = NULL; /*Lista com as distancias do no raiz aos demais nos*/
    listaDist *dist_aux = NULL; /*Lista auxiliar a dist*/

    minSet* N = NULL; /*subconjunto dos nos com caminho minimo ja definido*/
    minSet* N_aux = NULL;

    Grafo* grafo_aux = link_state; /*grafo com os caminhos da topologia*/

    int i, j;
    int u;

    printf("\n\nTABELA MENOR CUSTO: grafo_%d \n", raiz);
    /*imprimeTabela(link_state);*/

    /**
    *  Iniciliza todas as distancias como inifito,
    *  no caso, definido como INT_MAX da biblioteca limits.h
    *  e o subconjunto dos nos com as distancias minimas como 0
    */
    while(grafo_aux != NULL){
        dist_aux = (listaDist*)calloc(1, sizeof(listaDist));
        N_aux = (minSet*)calloc(1, sizeof(minSet));

        dist_aux->distancia = INT_MAX;
        dist_aux->no = grafo_aux->num;
        if(dist_aux->no == raiz){
            dist_aux->distancia = 0;
        }
        dist_aux->proximo = dist;
        dist = dist_aux;

        N_aux->no = grafo_aux->num;
        N_aux->marcador = 0;
        N_aux->proximo = N;
        N = N_aux;

        grafo_aux = grafo_aux->proximo;
    }

    /*Percorre todos os nos*/
    for(i = 0; i < qtd_nos; i++){
        /**
        * No com menor distancia entre os nos ainda não processados,
        * um no processado eh um no onde ja foi feito o calculo
        * da menor distancia em relacao ao no raiz
        */
        u = menorDistancia(dist, N);

        setProcessado(u, N);

        /*Para cada no percorrido verifica as distancias*/
        for(j = 0; j < qtd_nos; j++){
            int N_j = procuraProcessado(N, j);
            int no_grafo_u = procuraGrafoDist(link_state, dist, u, j);
            int dist_u = procuraDist(dist, u, 1);
            int dist_j = procuraDist(dist, j, 0);

            /*printf(":: %d, %d, %d, %d\n",N_j, no_grafo_u, dist_u, dist_j);*/

            /**
             * seta nova distancia minima caso:
             *  - no sendo verificado ainda nao tenha sido marcado como processado
             *  - nao seja no raiz, distancia == 0
             *  - distancia
             *  -
             */
            if (!N_j && no_grafo_u && (dist_u != INT_MAX) && (dist_u + no_grafo_u) < dist_j){
                setDist(dist, j, dist_u, no_grafo_u);
            }
        }
    }
    /*IMPRESSAO NA TELA DAS DISTANCIAS EM RELAÇÃO AO NO RAIZ*/
    char linha[20];
    char arqname[20];
    sprintf(arqname, "distance_%d.txt",raiz);
    while(dist_aux != NULL){
        printf("no:%d dist: %d\n", dist_aux->no, dist_aux->distancia);
        sprintf(linha,"no:%d dist: %d\n",dist_aux->no, dist_aux->distancia);
        gravaDistancia(arqname,linha);
        dist_aux = dist_aux->proximo;
    }
    free(dist);
    free(dist_aux);
}

/**
* [menorDistancia verifica proximo no com a menor distancia]
* @param  dist [lista das distancias]
* @param  N    [lista do subconjunto dos nos processados]
* @return      [retorna o menor no encontrado]
*/
int menorDistancia(listaDist* dist, minSet* N){

    int menor = INT_MAX;
    int menor_no;
    int i;
    listaDist* dist_aux = dist;

    for (i = 0; dist_aux != NULL; dist_aux = dist_aux->proximo, i++){
        int N_i = procuraProcessado(N, i);
        int dist_i = procuraDist(dist, i, 0);

        if ((N_i == 0) && (dist_i <= menor)){
            menor = dist_i;
            menor_no = procuraNo(dist, i);
        }
    }

    return menor_no;
}


/**
* [procuraProcessado verifica no subconjunto dos nos se o j-esimo no ja esta processado]
* @param  N [lista do subconjunto dos nos]
* @param  j [j-esimo no a ser verificado]
* @return   [retorna o valor encontrado, 0 no nao processado e 1 caso contrario]
*/
int procuraProcessado(minSet* N, int j){
    minSet* N_aux = N;
    int i;
    int processado = 0;

    for(i = 0; i < j; i++){
        N_aux = N_aux->proximo;
    }
    processado = N_aux->marcador;

    return processado;
}

/**
 * [procuraNo Procura i-esimo no]
 * @param  dist [lista com as distancias]
 * @param  i    [i-esimo termo]
 * @return      [retorna no na i-esima posicao]
 */
int procuraNo(listaDist* dist, int i){
    listaDist* dist_aux = dist;
    int k;
    int no = 0;

    for(k = 0; k < i; k++){
        dist_aux = dist_aux->proximo;
    }
    no = dist_aux->no;

    return no;
}

/**
* [procuraGrafo Procura a distancia no grafo]
* @param  grafo [Grafo da topologia]
* @param  u     [no selecionado com a menor distancia]
* @param  j     [j-esimo vizinho de u]
* @return       [retorna distancia do no u em relação ao vizinho j]
*/
int procuraGrafoDist(Grafo* grafo, listaDist* dist, int u, int j){
    Grafo* grafo_aux = grafo;
    listaDist* dist_aux = dist;
    Lista_vizinho* no_vizinhos = NULL;

    int achou = 0, i;

    /*Vai para o no u*/
    while((grafo_aux != NULL) && (achou == 0)){
        if(grafo_aux->num == u){
            no_vizinhos = grafo_aux->vizinho;
            achou = 1;
        }else{
            grafo_aux = grafo_aux->proximo;
        }
    }

    for(i = 0; i < j; i++){
        dist_aux = dist_aux->proximo;
    }

    achou = 0;

    /*Percorre vizinhos do no u de acordo com a lista de vizinhos*/
    while((no_vizinhos != NULL) && (achou == 0)){
        if(no_vizinhos->vizinho == dist_aux->no){
            return no_vizinhos->custo;
            achou = 1;
        }else{
            no_vizinhos = no_vizinhos->proximo;
        }
    }

    return 0;
}

/**
* [procuraDist Procura distancia na lista de distancias]
* @param  dist [lista de distancias]
* @param  j    [j-esima posicao na lista ou no u]
* @param tipo  [caso j seja uma posicao ou caso seja o no setado como menor distancia]
* @return      [retorna distancia]
*/
int procuraDist(listaDist* dist, int j, int tipo){
    listaDist* dist_aux = dist;
    int i;
    int distancia = 0;

    if(tipo == 0){
        for(i = 0; i < j; i++){
            dist_aux = dist_aux->proximo;
        }
        distancia = dist_aux->distancia;
    }else{
        int achou = 0;
        while((dist_aux != NULL) && (achou == 0)){
            if(dist_aux->no == j){
                distancia = dist_aux->distancia;
                achou = 1;
            }else{
                dist_aux = dist_aux->proximo;
            }
        }
    }

    return distancia;
}

/**
* [setDist seta distancia na lista de distancias]
* @param dist       [lista de distancias]
* @param j          [j-esima posicao]
* @param dist_u     [distancia em relacao ao no u, menor distancia em relacao no anterior]
* @param no_grafo_u [distancia encontrada no grafo]
*/
void setDist(listaDist* dist, int j, int dist_u, int no_grafo_u){
    int i;
    listaDist* dist_aux = dist;

    for(i = 0; i < j; i++){
        dist_aux = dist_aux->proximo;
    }

    dist_aux->distancia = dist_u + no_grafo_u;

    dist = dist_aux;
}

/**
* [setProcessado Seta valor true, 1, para um no]
* @param u [valor no processado]
* @param N [lista do subconjunto dos nos processados]
*/
void setProcessado(int u, minSet* N){
    int achou = 0;
    minSet* N_aux = N;

    while((N_aux != NULL) && (achou == 0)){
        if(N_aux->no == u){
            N_aux->marcador = 1;
            achou = 1;
        }else{
            N_aux = N_aux->proximo;
        }
    }
    N = N_aux;
}
