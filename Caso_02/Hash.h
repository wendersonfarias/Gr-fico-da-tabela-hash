#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "DoublyLinkedList.h"

//Bloco para escolha do tamanho da tabela hash
//#define MAX 10000 // tabela 100 x 100
//#define MAX 4900 // tabela 70 x 70
#define MAX 3025 // tabela 55 x 55

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
int raiz_Qd();

#endif // HASH_H_INCLUDED
