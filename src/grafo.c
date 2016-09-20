#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

/**
* [escreveTabelaTopologia Função que faz a distribuição dos dados dos nos
* e seus vizinhos para todos os outros nos, para que todos nos fiquem
* com a toda informação da topologia]
* @param  no [No da topologia]
* @return    [int como sendo uma variavel de controle, caso seja retornado
*              1 o programa continua distribuindo os dados dos nos, caso
*              contrario todos os nos já possuem a topologia total]
*/
int escreveTabelaTopologia(Grafo* no){
    Grafo* src_aux = no;

    FILE* grafo_no;
    FILE* grafo_vizinho;

    String* nome_arquivo = NULL;
    String* nome_arquivo_aux = NULL;

/*
    Lista_vizinho* aux_no = no->vizinho;
    int sair = 0;
    int encontrou = 0;
    char c_aux;
    char c[2];
    char no_vizinho[10];
*/
    int troca = 0;

    grafo_no = fopen(src_aux->grafo,"r");

    /*Parte da tabela de topologia de cada no*/
    if(grafo_no == NULL){/*cria arquivo caso nao exista*/
        grafo_no = fopen(src_aux->grafo,"w");
        fprintf(grafo_no, "%d;", src_aux->num);
        Lista_vizinho *lista_vizinho_aux = src_aux->vizinho;
        for(;lista_vizinho_aux != NULL; lista_vizinho_aux = lista_vizinho_aux->proximo){
            fprintf(grafo_no, "%d[%d];", lista_vizinho_aux->vizinho, lista_vizinho_aux->custo);
            nome_arquivo_aux = calloc(1, sizeof(String));
            sprintf(nome_arquivo_aux->nome_arquivo, "grafo_%d.txt", lista_vizinho_aux->vizinho);
            nome_arquivo_aux->proximo = nome_arquivo;
            nome_arquivo = nome_arquivo_aux;
        }
        fclose(grafo_no);
    }else{ /*se ja existir verifica se a linha do proprio no esta na tabela*/
        int tem_na_tabela_topologia = false; /*parte do pressuposto que nao tem a linha na tabela*/
        int i;
        size_t len = 0;
        char *vizinho_string_aux = NULL;
        char num_aux[5];

        while(getdelim(&vizinho_string_aux,&len,'\n',grafo_no) != -1){
            for(i = 0;vizinho_string_aux[i] !=';';i++){
                num_aux[i] = vizinho_string_aux[i];
            }
            if(src_aux->num == atoi(num_aux)){
                tem_na_tabela_topologia = true;
            }
        }
        free(vizinho_string_aux);
        fclose(grafo_no);
        if(tem_na_tabela_topologia == false){/*se nao tiver a linha adiciona*/
            grafo_no = fopen(src_aux->grafo,"a");
            fprintf(grafo_no, "\n");
            fprintf(grafo_no, "%d;", src_aux->num);
            Lista_vizinho *lista_vizinho_aux = src_aux->vizinho;
            for(;lista_vizinho_aux != NULL; lista_vizinho_aux = lista_vizinho_aux->proximo){
                fprintf(grafo_no, "%d[%d];", lista_vizinho_aux->vizinho, lista_vizinho_aux->custo);
                nome_arquivo_aux = calloc(1, sizeof(String));
                sprintf(nome_arquivo_aux->nome_arquivo, "grafo_%d.txt", lista_vizinho_aux->vizinho);
                nome_arquivo_aux->proximo = nome_arquivo;
                nome_arquivo = nome_arquivo_aux;
            }
            fclose(grafo_no);
        }else{
            Lista_vizinho *lista_vizinho_aux = src_aux->vizinho;
            for(;lista_vizinho_aux != NULL; lista_vizinho_aux = lista_vizinho_aux->proximo){
                nome_arquivo_aux = calloc(1, sizeof(String));
                sprintf(nome_arquivo_aux->nome_arquivo, "grafo_%d.txt", lista_vizinho_aux->vizinho);
                nome_arquivo_aux->proximo = nome_arquivo;
                nome_arquivo = nome_arquivo_aux;
            }
        }
    }

    /*parte de divulgar ao vizinhos a tabela de cada no*/
    while(nome_arquivo != NULL){ /*para cada vizinho*/
        grafo_vizinho = fopen(nome_arquivo->nome_arquivo, "r");
        if(grafo_vizinho == NULL){/*se o arquivo de tabela de topologia do vizinho nao existe, cria*/
            char *no_string_aux = NULL;
            size_t len = 0;
            grafo_vizinho = fopen(nome_arquivo->nome_arquivo,"w");
            grafo_no = fopen(src_aux->grafo,"r");
            while(getdelim(&no_string_aux,&len,'\n',grafo_no) != -1){
                fprintf(grafo_vizinho, "%s",no_string_aux);
            }
            free(no_string_aux);
            fclose(grafo_no);
            fclose(grafo_vizinho);
            troca++;
        }else{ /*se ja existe, para cada vizinho verifica se a linha ja foi adicionada*/
            int tem_na_tabela_topologia = false; /*parte do pressuposto que nao tem a linha na tabela*/
            int i,j;
            size_t len_no = 0;
            char *no_string_aux = NULL;
            char no_num_aux[5];
            char vizinho_num_aux[5];

            grafo_no = fopen(src_aux->grafo, "r");

            while (getdelim(&no_string_aux,&len_no,'\n',grafo_no) != -1) {
                size_t len_vizinho = 0;
                char *vizinho_string_aux = NULL;
                tem_na_tabela_topologia = false;
                for(i = 0;no_string_aux[i] !=';';i++){
                    no_num_aux[i] = no_string_aux[i];
                }
                grafo_vizinho = fopen(nome_arquivo->nome_arquivo, "r");
                while (getdelim(&vizinho_string_aux,&len_vizinho,'\n',grafo_vizinho) != -1) {
                    for(j = 0;vizinho_string_aux[j] !=';';j++){
                        vizinho_num_aux[j] = vizinho_string_aux[j];
                    }
                    if(atoi(no_num_aux) == atoi(vizinho_num_aux)){
                        tem_na_tabela_topologia = true;
                    }
                }
                free(vizinho_string_aux);
                fclose(grafo_vizinho);
                if(tem_na_tabela_topologia == false){
                    cutStringOnChar(no_string_aux,'\n');
                    grafo_vizinho = fopen(nome_arquivo->nome_arquivo, "a");
                    fprintf(grafo_vizinho, "\n%s",no_string_aux);
                    fclose(grafo_vizinho);
                    troca++;
                }
            }
            fclose(grafo_no);
            free(no_string_aux);
        }
        nome_arquivo_aux = nome_arquivo;
        nome_arquivo = nome_arquivo->proximo;
        free(nome_arquivo_aux);
    }
    return troca;
}

/*Funcao auxiliar para remover os '\n' das strings e nao acontecer
* de adicionar indevidamente '\n' nos arquivos*/
void cutStringOnChar(char s[], char c){
    int i;
    for(i = 0; i < strlen(s); i++){
        if(s[i] == c){
            s[i] = '\0';
        }
    }
    return;
}

/**
* [imprimeTabela Função para impressão do grafo gravado gerado pela leitura do
* arquivo da topologia]
* @param link_state [grafo da topologia a ser impressa]
*/
void imprimeTabela(Grafo* link_state){
    Grafo* aux = link_state;
    /**
    * percorre grafo
    */
    for(;aux != NULL; aux = aux->proximo){
        printf("no: %d\n", aux->num);
        Lista_vizinho* lista = aux->vizinho;
        for(;lista != NULL; lista = lista->proximo){
            printf("\tvizinho: %d", lista->vizinho);
            printf("\tcusto: %d\n", lista->custo);
        }
    }
    return;
}

void imprimeTabelaGrafo(){

}
