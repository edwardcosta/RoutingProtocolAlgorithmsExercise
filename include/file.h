#ifndef FILE_H
#define FILE_H

typedef struct no_aux{
    int vizinho;
    int custo;
    struct no_aux* proximo;
}Lista_vizinho;

typedef struct no{
    int num;    // numero do no
    FILE* grafo;
    FILE* tabela;
    Lista_vizinho* vizinho;
    struct no* proximo;
}Grafo;

Grafo* loadFile(char* filename);

Grafo* constroiTabela(int no, Lista_vizinho* lista_no_aux);

void imprimeTabela(Grafo* link_state);


#endif
