#include "file.h"

void loadFIle(char* file_name){
    // strcat(file_name, ".txt");
    //
    // FILE *arq;
    int c;
    int sair;
    int no;
    int vizinho;
    int custo;
    //
    // arq = fopen(file_name,"r");
    //
    // while(fscanf(arq, "%d", &no) != EOF){ // le no
    //     printf("no:%d \n", no);
    //     while(fscanf(arq, "%c ", &c)){
    //         fscanf(arq, "%d", &vizinho);
    //         fgetc(arq);
    //         fscanf(arq, "%d", &custo);
    //         fgetc(arq);
    //
    //         printf("\tvizinho:%d custo:%d\n", vizinho, custo);
    //         getchar();
    //     }
    // }
    // fclose(arq);
    while(fim != 1 ){
        printf("no: ");
        scanf("%d", &no);
        while(c != 1){
            printf("v: ");
            scanf("%d", &vizinho);
            printf("c: ");
            scanf("%d", &custo);
            printf("char: ");
            scanf("%d", &c);
            printf("fim: ");
            scanf("%d", &fim);
        }
    }
}
