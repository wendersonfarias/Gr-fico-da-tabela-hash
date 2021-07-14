#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"


typedef struct Palavra {
    char texto[50];
}Palavra;
bool comparaChaves(void *key, void *data) {
    char *chave = (char*)key;
    Palavra *c = (Palavra*)data;

    return (strcmp (chave, c->texto) == 0)?true:false;
}
/*
void LeTxt(void *key,void *data) {
    Palavra *palavra = (Palavra*)data;
    Palavra *c = (Palavra *)malloc(sizeof(Palavra));
    //printf("{%s} - ", palavra->texto);
    char url[]="lista.txt";
    FILE *arq;
    arq = fopen(url, "r");
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while( ! feof(arq)){
            c = (Palavra *)malloc(sizeof(Palavra));
            fscanf(arq, "%s", &c->texto);
            put(&hashes, c->texto, c, comparaChaves);
        }
        fclose(arq);
}*/
void printPalavra(void *data) {
    Palavra *palavra = (Palavra*)data;
    printf("{%s} - ", palavra->texto);
}
float porcentagemHash(void *data){
    int i;
    Palavra *palavra = (Palavra*)data;
    float porcent = 0, cont  = 0;
    for(i = 0; i < MAX; i++){
        if(palavra->texto[i] != NULL){
            cont++;
        }
    }
    porcent = (cont*100)/MAX;
    return(porcent);
}
int main() {
    HashStruct hashes;
    initHash(&hashes);
    Palavra *c = (Palavra *)malloc(sizeof(Palavra));

    //Abre o arquivo, faz a leitura e grava na tabela
    char url[]="lista.txt";
    FILE *arq;
    arq = fopen(url, "r");
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while(!feof(arq)){
            c = (Palavra *)malloc(sizeof(Palavra));
            fscanf(arq, "%s", &c->texto);
            put(&hashes, c->texto, c, comparaChaves);
        }
        fclose(arq);
    //Calcula a porcentagem de ocupacao da tabela
    float p100=porcentagemHash(&hashes);
    showHashStruct(&hashes, printPalavra);
    printf("\nPorcentagem >>> %.f porcento",p100);


    /*O procedimento imprimeColisaon mostra uma posicao
e todas as suas colisoes.*/
/*
void imprimeColisao(Hash tab, int pos){
 Dados* aux = tab[pos];
 if(aux == NULL){
  printf("Esta posicao esta vazia!");
  return;
 }else{
  if(aux != NULL){
   printf("%3d",aux->info);
   while(aux->prox != NULL){
    printf(" -> %d",aux->prox->info);
    aux = aux->prox;
   }
  }
 }
}
    */


    return 0;
}
