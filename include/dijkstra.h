#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct custo{
    int distancia;
    int no;
    struct custo* proximo;
}listaDist;

typedef struct N{
    int no;
    int marcador;
    struct N* proximo;
}minSet;

void dijkstraLista(Grafo* link_state, int qtd_nos, int raiz);

int menorDistancia(listaDist* dist, minSet* N);

int procuraProcessado(minSet* N, int j);
int procuraNo(listaDist* dist, int i);
int procuraGrafoDist(Grafo* grafo, listaDist* dist, int u, int j);
int procuraDist(listaDist* dist, int j, int tipo);

void setDist(listaDist* dist, int j, int dist_u, int no_grafo_u);
void setProcessado(int u, minSet* N);





#endif
