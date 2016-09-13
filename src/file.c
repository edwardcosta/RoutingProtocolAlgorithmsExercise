#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"


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
    char vizinho[10];
    char custo[10];

    arq = fopen(file_name,"r");

    if(arq != NULL){
        while(sair != 1){ // le no
            c_aux = fgetc(arq);
            c[0] = c_aux;
            c[1] = '\0';
            strcpy(no, c);
            while((c_aux = fgetc(arq)) != ';'){
                c[0] = c_aux;
                c[1] = '\0';
                strcat(no, c);
            }
            // printf("no:%s\n", no);
            lista_no = NULL;
            lista_no_aux = NULL;
            while((c_aux = fgetc(arq))!= '\n'){
                if(c_aux == EOF){
                    sair = 1;
                    break;
                }
                c[0] = c_aux;
                c[1] = '\0';
                strcpy(vizinho, c);
                while((c_aux = fgetc(arq)) != '['){
                    c[0] = c_aux;
                    c[1] = '\0';
                    strcat(vizinho, c);
                }
                c_aux = fgetc(arq);
                c[0] = c_aux;
                c[1] = '\0';
                strcpy(custo, c);
                while((c_aux = fgetc(arq)) != ']'){
                    c[0] = c_aux;
                    c[1] = '\0';
                    strcat(custo, c);
                }
                fgetc(arq);

                lista_no_aux = calloc(1,sizeof(Lista_vizinho));
                lista_no_aux->vizinho = atoi(vizinho);
                lista_no_aux->custo = atoi(custo);
                lista_no_aux->proximo = lista_no;
                lista_no = lista_no_aux;
                // printf("\tvizinho:%d custo:%d\n", lista_no_aux->vizinho, lista_no_aux->custo);
            }
            link_state_aux = constroiTabela(atoi(no), lista_no);
            link_state_aux->proximo = link_state;
            link_state = link_state_aux;
        }
        fclose(arq);
    }else{
        printf("ERROR: nao foi possivel abrir o arquivo com a topologia especificada\n");
        printf("verifique o nome inserido e tente novamente.\n");
    }
    // imprimeTabela(link_state);
    return link_state;
}

Grafo* constroiTabela(int no, Lista_vizinho* lista_no){

    Grafo* constroi = NULL;

    constroi = calloc(1, sizeof(Grafo));

    constroi->num = no;
    constroi->vizinho = lista_no;

    return constroi;
}

void escreveTabelaTopografia(Grafo* src, Grafo* dst){
    Grafo* src_aux = src;
    Grafo* dst_aux = dst;
    char filename[10];

    sprintf(filename,"%d.txt",dst_aux->num);

    dst_aux->grafo = fopen(filename,"r");

    if(src_aux->grafo == NULL){
        dst_aux->grafo = fopen(filename,"w");
        fprintf(dst->grafo, "\n", );
    }
}

void imprimeTabela(Grafo* link_state){
    Grafo* aux = link_state;
    for(;aux != NULL; aux = aux->proximo){
        printf("no: %d\n", aux->num);
        Lista_vizinho* lista = aux->vizinho;
        for(;lista != NULL; lista = lista->proximo){
            printf("\tvizinho: %d", lista->vizinho);
            printf("\tcusto: %d\n", lista->custo);
        }
    }
}
