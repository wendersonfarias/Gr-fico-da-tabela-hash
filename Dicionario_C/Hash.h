#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "DoublyLinkedList.h"
#define MAX 3600 // tabela 60 x 60
//#define MAX 3025 // tabela 55 x 55
//#define MAX 1225 // tabela 35 x 35
//#define MAX 2025 // tabela 45 x 45

typedef struct HashStruct {//Struct para manipular a tabela hash
    DoublyLinkedList hashes[MAX];
    int size;
}HashStruct;

typedef struct Palavra {//Struct para armazenar os dados das listas.
    char texto[50];
}Palavra;

void initHash(HashStruct *hashStruct);
int hash(char *key);
bool isHashEmpty(HashStruct *hashStruct);
bool containsKey(HashStruct *hashStruct, char *key, compare equal);
bool comparaChaves(void *key, void *data);
int put(HashStruct *hashStruct, char *key, void *data, compare equal);
void* get(HashStruct *hashStruct, char *key, compare equal);
void* removeKey(HashStruct *hashStruct, char *key, compare equal);
void showHashStruct(HashStruct *hashStruct, printNode print);
void printPalavra(void *data);
void imprimeColisoes(HashStruct *hashStruct, printNode print);
void mapaEspalhamento(HashStruct *hashStruct);
void carregaArquivo(HashStruct *hashStruct,Palavra *t_palavra);
void porcentagemHash(HashStruct *hashStruct);
int raiz_quadrada ();

#endif // HASH_H_INCLUDED
