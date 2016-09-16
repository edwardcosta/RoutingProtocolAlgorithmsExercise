/**
*
*/
#ifndef GRAFO_H
#define GRAFO_H

#define true 1
#define false 0

typedef struct no_aux{
    int vizinho;
    int custo;
    struct no_aux* proximo;
}Lista_vizinho;

typedef struct no{
    int num;    // numero do no
    char grafo[20];
    char tabela[20];
    Lista_vizinho* vizinho;
    struct no* proximo;
}Grafo;

typedef struct string{
    char nome_arquivo[20];
    struct string* proximo;
}String;

int escreveTabelaTopologia(Grafo* no);
void imprimeTabela(Grafo* link_state);

void imprimeTabelaGrafo();

void cutStringOnChar(char s[], char c);

void dijkstraLista();

#endif
