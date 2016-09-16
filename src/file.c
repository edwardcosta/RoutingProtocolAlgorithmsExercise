#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char vizinho[10];
    char custo[10];

    arq = fopen(file_name,"r");

    if(arq != NULL){
        /**
        * Percorre arquivo até o final
        */
        while(sair != 1){ // le no
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
            while((c_aux = fgetc(arq))!= '\n'){
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
                // printf("\tvizinho:%d custo:%d\n", lista_no_aux->vizinho, lista_no_aux->custo);
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
    // imprimeTabela(link_state);
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
    Lista_vizinho* aux_no = no->vizinho;

    FILE* grafo_no;
    FILE* grafo_vizinho;

    String* nome_arquivo = NULL;
    String* nome_arquivo_aux = NULL;

    int sair = 0;
    int encontrou = 0;
    char c_aux;
    char c[2];
    char no_vizinho[10];
    int troca = false;

    grafo_no = fopen(src_aux->grafo,"r");

    printf("No %d\n",src_aux->num);
    getchar();

    /*Parte da tabela de tepologia de cada no*/
    if(grafo_no == NULL){/*cria arquivo caso nao exista*/
        printf("%d criar tabela %s",src_aux->num,src_aux->grafo);
        getchar();
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
        fprintf(grafo_no, "\n");
        fclose(grafo_no);
    }else{ /*se ja existir verifica se a linha do proprio no esta na tabela*/
        int tem_na_tabela_topologia = false; /*parte do pressuposto que nao tem a linha na tabela*/
        int i;
        size_t len = 0;
        char *vizinho_string_aux = NULL;
        char num_aux[5];

        printf("%s ja existe\n",src_aux->grafo);
        getchar();

        while(getline(&vizinho_string_aux,&len,grafo_no) != -1){
            for(i = 0;vizinho_string_aux[i] !=';';i++){
                num_aux[i] = vizinho_string_aux[i];
            }
            printf("vizinho %d na tabela\n", atoi(num_aux));
            getchar();
            if(src_aux->num == atoi(num_aux)){
                tem_na_tabela_topologia = true;
            }
        }
        fclose(grafo_no);
        if(tem_na_tabela_topologia == false){/*se nao tiver a linha adiciona*/
            printf("escrever %d na tabela %s\n", src_aux->num,src_aux->grafo);
            grafo_no = fopen(src_aux->grafo,"a");
            fprintf(grafo_no, "%d;", src_aux->num);
            Lista_vizinho *lista_vizinho_aux = src_aux->vizinho;
            for(;lista_vizinho_aux != NULL; lista_vizinho_aux = lista_vizinho_aux->proximo){
                fprintf(grafo_no, "%d[%d];", lista_vizinho_aux->vizinho, lista_vizinho_aux->custo);
                nome_arquivo_aux = calloc(1, sizeof(String));
                sprintf(nome_arquivo_aux->nome_arquivo, "grafo_%d.txt", lista_vizinho_aux->vizinho);
                nome_arquivo_aux->proximo = nome_arquivo;
                nome_arquivo = nome_arquivo_aux;
            }
            fprintf(grafo_no, "\n");
            fclose(grafo_no);
        }
    }

    /*parte de divulgar ao vizinhos a tabela de cada no*/
    for(;nome_arquivo != NULL; nome_arquivo = nome_arquivo->proximo){ /*para cada vizinho*/
        printf("%s\n",nome_arquivo->nome_arquivo);
        getchar();
        grafo_vizinho = fopen(nome_arquivo->nome_arquivo, "r");
        if(grafo_vizinho == NULL){/*se o arquivo de tabela de topologia do vizinho nao existe, cria*/
            char *no_string_aux = NULL;
            size_t len = 0;
            printf("%s criar tabela\n",nome_arquivo->nome_arquivo);
            getchar();
            grafo_vizinho = fopen(nome_arquivo->nome_arquivo,"w");
            grafo_no = fopen(src_aux->grafo,"r");
            while(getline(&no_string_aux,&len,grafo_no) != -1){
                printf("%s\n", no_string_aux);
                getchar();
                fputs(no_string_aux, grafo_vizinho);
            }
            fclose(grafo_no);
            fclose(grafo_vizinho);
            troca = true;
        }else{ /*se ja existe, para cada vizinho verifica se a linha ja foi adicionada*/
            int tem_na_tabela_topologia = false; /*parte do pressuposto que nao tem a linha na tabela*/
            int i,j;
            size_t len_no = 0;
            size_t len_vizinho = 0;
            char *no_string_aux = NULL;
            char *vizinho_string_aux = NULL;
            char no_num_aux[5];
            char vizinho_num_aux[5];

            printf("%s ja tem tabela\n",nome_arquivo->nome_arquivo);
            getchar();

            grafo_no = fopen(src_aux->grafo, "r");

            while (getline(&no_string_aux,&len_no, grafo_no) != -1) {
                tem_na_tabela_topologia = false;
                for(i = 0;no_string_aux[i] !=';';i++){
                    no_num_aux[i] = no_string_aux[i];
                }
                grafo_vizinho = fopen(nome_arquivo->nome_arquivo, "r");
                while (getline(&vizinho_string_aux,&len_vizinho,grafo_vizinho) != -1) {
                    for(j = 0;vizinho_string_aux[j] !=';';j++){
                        vizinho_num_aux[j] = vizinho_string_aux[j];
                    }
                    printf("%d\n%d\n",atoi(no_num_aux),atoi(vizinho_num_aux));
                    getchar();
                    if(atoi(no_num_aux) == atoi(vizinho_num_aux)){
                        tem_na_tabela_topologia = true;
                    }
                }
                fclose(grafo_vizinho);
                if(tem_na_tabela_topologia == false){
                    printf("Escreve na tabela\n");
                    grafo_vizinho = fopen(nome_arquivo->nome_arquivo, "a");
                    fprintf(grafo_vizinho, "%s\n",no_string_aux);
                    fclose(grafo_vizinho);
                    troca = true;
                }
            }
            fclose(grafo_no);
        }
    }
    return troca;
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
}

void imprimeTabelaGrafo(){

}
