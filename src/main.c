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
 *
 *
 */
#include "file.h"
#include "main.h"

typedef struct roteador{
    int num;
    FILE *arq;
    struct roteador* vizinho;
}Roteador;

typedef struct lista{
    Roteador* roteador;
    struct lista* next;
}Lista;

int main(int argc, char **argv) {

    if(argc != 2){
        printf("\nERROR: numero de argumentos de entrada inválido\n");
        printf("formato entrada: ./main nome_topologia\n");
    }else{
        char nome_topologia[20];
        strcpy(nome_topologia, argv[1]);
        loadFile(nome_topologia);
    }
    return 0;
}
