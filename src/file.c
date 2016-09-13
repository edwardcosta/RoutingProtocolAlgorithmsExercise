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
            if((c_aux = fgetc(arq)) == EOF){
                sair = 1;
                break;
            }
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

    sprintf(constroi->grafo, "grafo_%d.txt", no);

    return constroi;
}

int escreveTabelaTopologia(Grafo* no){
    Grafo* src_aux = no;
    Lista_vizinho* aux_no = no->vizinho;

    FILE* grafo_no;
    FILE* grafo_vizinho;

    char nome_arquivo[20];
    char vizinhos[50];
    char aux[10];

    int sair = 0;
    int encontrou = 0;
    char c_aux;
    char c[2];
    char no_vizinho[10];
    int troca = 1;

    grafo_no = fopen(src_aux->grafo,"r");

    if(grafo_no != NULL){
        printf("ola entrei! %d ", src_aux->num);
        grafo_no = fopen(src_aux->grafo,"w");
        fprintf(grafo_no, "%d;", src_aux->num);
        sprintf(vizinhos, "%d;" ,src_aux->num);
        while(src_aux->vizinho != NULL){
            fprintf(grafo_no, "%d[%d];", src_aux->vizinho->vizinho, src_aux->vizinho->custo);
            sprintf(nome_arquivo, "grafo_%d.txt", src_aux->vizinho->vizinho);
            sprintf(aux,"%d[%d];", src_aux->vizinho->vizinho, src_aux->vizinho->custo);
            strcat(vizinhos, aux);
            src_aux->vizinho = src_aux->vizinho->proximo;
        }
        fprintf(grafo_no, "\n");
        sprintf(vizinhos, "\n");
        while(aux_no != NULL){
            grafo_vizinho = fopen(nome_arquivo, "r");
            if(grafo_vizinho != NULL){
                while(sair != 1){ // le no
                    if((c_aux = fgetc(grafo_vizinho)) == EOF){
                        sair = 1;
                        break;
                    }
                    c[0] = c_aux;
                    c[1] = '\0';
                    strcpy(no_vizinho, c);
                    while((c_aux = fgetc(grafo_vizinho)) != ';'){
                        c[0] = c_aux;
                        c[1] = '\0';
                        strcat(no_vizinho, c);
                    }
                    //printf("no:%s\n", no_vizinho);
                    while((c_aux = fgetc(grafo_vizinho))!= '\n');

                    if(src_aux->num == atoi(no_vizinho)){
                        encontrou = 1;
                    }
                }
                if(encontrou != 1){
                    grafo_vizinho = fopen(nome_arquivo, "w");
                    fprintf(grafo_vizinho, "%s", vizinhos);
                    fclose(grafo_vizinho);
                    troca = 0;
                }
            }
            aux_no = aux_no->proximo;
        }
    }else{
        printf("ERROR: problema ao criar tabelas dos nos");
    }
    return troca;
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

void imprimeTabelaGrafo(){

}
