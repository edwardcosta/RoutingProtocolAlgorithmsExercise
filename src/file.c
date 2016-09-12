#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadFile(char* file_name){
    strcat(file_name, ".txt");

    FILE *arq;
    int sair;
    int c_aux;
    char c[2];
    char no[10];
    char vizinho[10];
    char custo[10];

    arq = fopen(file_name,"r");

    if(arq != NULL){
        // printf(" %s")
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
            printf("no:%s\n", no);
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

                printf("\tvizinho:%s custo:%s\n", vizinho, custo);
                // getchar();
            }
        }
        fclose(arq);
    }else{
        printf("ERROR: nao foi possivel abrir o arquivo com a topologia especificada\n");
        printf("verifique o nome inserido e tente novamente.\n");
    }
}
