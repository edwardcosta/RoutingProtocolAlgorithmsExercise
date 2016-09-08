#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "file.h"

typedef struct roteador{
  int num;
  FILE *arq;
  struct roteador* vizinho;
}Roteador;

typedef struct lista{
  Roteador* roteador;
  struct lista* next;
}Lista;

int main(int argc, char const *argv[]) {
  /* variables */
  char no[20];
  /* code */
  printf("Hello World\n");
  return 0;
}

void menu(){
  printf("Inclua o nó e seus vizinhos:\n", );
  scanf("%s\n", );
}
