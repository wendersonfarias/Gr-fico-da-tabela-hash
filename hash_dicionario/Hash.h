#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "DoublyLinkedList.h"
#define MAX 3025 // tabela 55 x 55

//Operações
//isHashEmpty: verifica se a tabela de hash está vazia;
//hash: calcula o hash para a chave;
//put: insere um par (chave,valor);
//containsKey: verifica se a chave já existe na tabela de hash;
//get: retorna o valor buscando pela chave;
//removeKey: remove um par (chave,valor);
//showHashStruct: exibe os pares armazenados

typedef struct HashStruct {
    DoublyLinkedList hashes[MAX];
    int size;
}HashStruct;

typedef struct Palavra {
    char texto[50];
}Palavra;

void initHash(HashStruct *hashStruct);
bool isHashEmpty(HashStruct *hashStruct);
int hash(char *key);
int put(HashStruct *hashStruct, char *key, void *data, compare equal);
bool containsKey(HashStruct *hashStruct, char *key, compare equal);
void* get(HashStruct *hashStruct, char *key, compare equal);
void* removeKey(HashStruct *hashStruct, char *key, compare equal);
void showHashStruct(HashStruct *hashStruct, printNode print);
void imprimeColisoes(HashStruct *hashStruct, printNode print);
void mapaColisoes(HashStruct *hashStruct, printNode print);
void carregaArquivo(HashStruct *hashStruct,Palavra *t_palavra);
bool comparaChaves(void *key, void *data);
void printPalavra(void *data);
void porcentagemHash(HashStruct *hashStruct);

#endif // HASH_H_INCLUDED
