#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "file.h"

/**
* [loadFile description]
* @param  file_name [Arquivo com os nós da topologia]
* @return           [Grafo com nós e vizinhos e custos]
*/
Grafo* loadFile(char* file_name){
    strcat(file_name, ".txt");

    Lista_vizinho* lista_no = NULL;
    Lista_vizinho* lista_no_aux = NULL;

    Grafo* link_state = NULL;
    Grafo* link_state_aux = NULL;

    FILE *arq;
    int sair;
    int c_aux;
    char c[2];
    char no[10];
    char vizinho[50];
    char custo[50];

    arq = fopen(file_name,"r");

    if(arq != NULL){
        /**
        * Percorre arquivo até o final
        */
        while(sair != 1){ /* le no */
            if((c_aux = fgetc(arq)) == EOF){
                sair = 1;
                break;
            }
            /**
            * Le o valor do no
            */
            c[0] = c_aux;
            c[1] = '\0';
            strcpy(no, c);
            while((c_aux = fgetc(arq)) != ';'){
                c[0] = c_aux;
                c[1] = '\0';
                strcat(no, c);
            }
            lista_no = NULL;
            lista_no_aux = NULL;
            /**
            * le vizinho e custo enquanto nao passar para o outro no
            */
            while((c_aux = fgetc(arq)) != '\n'){
                if((c_aux) == EOF){
                    sair = 1;
                    break;
                }
                /**
                * le vizinho
                */
                c[0] = c_aux;
                c[1] = '\0';
                strcpy(vizinho, c);
                while((c_aux = fgetc(arq)) != '['){
                    c[0] = c_aux;
                    c[1] = '\0';
                    strcat(vizinho, c);
                }
                c_aux = fgetc(arq);
                /**
                * le custo
                */
                c[0] = c_aux;
                c[1] = '\0';
                strcpy(custo, c);
                while((c_aux = fgetc(arq)) != ']'){
                    c[0] = c_aux;
                    c[1] = '\0';
                    strcat(custo, c);
                }
                fgetc(arq);

                /**
                * Insere os vizinhos e custos lidos do no e os insere em uma lista
                */
                lista_no_aux = calloc(1,sizeof(Lista_vizinho));
                lista_no_aux->vizinho = atoi(vizinho);
                lista_no_aux->custo = atoi(custo);
                lista_no_aux->proximo = lista_no;
                lista_no = lista_no_aux;
                /* printf("\tvizinho:%d custo:%d\n", lista_no_aux->vizinho, lista_no_aux->custo); */
            }
            /**
            * Com a lista dos vizinhos do no pronta eh gerado um no no Grafo
            * com o no lido e seus vizinhos
            */
            link_state_aux = constroiTabela(atoi(no), lista_no);
            link_state_aux->proximo = link_state;
            link_state = link_state_aux;
        }
        fclose(arq);
    }else{
        printf("ERROR: nao foi possivel abrir o arquivo com a topologia especificada\n");
        printf("verifique o nome inserido e tente novamente.\n");
    }
    /* imprimeTabela(link_state); */
    return link_state;
}

/**
* [constroiTabela Para cada no é criado um espaço dentro do grafo que
* ira receber a topologia total]
* @param  no       [valor do no]
* @param  lista_no [Lista dos vizinhos associados ao no]
* @return Grafo    [retorna os dados na forma de grafo para ser adicionada
*                   no grafo principal]
*/
Grafo* constroiTabela(int no, Lista_vizinho* lista_no){

    Grafo* constroi = NULL;

    constroi = calloc(1, sizeof(Grafo));

    constroi->num = no;
    constroi->vizinho = lista_no;

    /**
    * Cada no possui uma tabela com a informação do grafo a ser preenchida
    */
    sprintf(constroi->grafo, "grafo_%d.txt", no);

    return constroi;
}

void gravaDistancia(char *arqname, char *linha){
    FILE *arq;
    arq = fopen(arqname,"a");
    if(arq != NULL){
        fprintf(arq, "%s",linha);
    }
    fclose(arq);
}
