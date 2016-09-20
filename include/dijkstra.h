#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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

    void dijkstraLista(Grafo* link_state, int qtd_nos, int raiz);
    int ehVizinho(int vizinho, Grafo* link_state);
    void imprimeTabelaCusto(Dv* custo);
    int completo(subN* N);
    
#endif
