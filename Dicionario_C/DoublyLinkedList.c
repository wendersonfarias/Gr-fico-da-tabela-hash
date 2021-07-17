#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"

//Inicia a lista circular com o recurso do nó sentinela.
void init(DoublyLinkedList *list) {
//trashNode: Nó sentinela (permite que mesmo a lista estando vazia ela aponta para um nó: (list->first=trashNode;)
    Node *trashNode = (Node*)malloc(sizeof(Node));
    trashNode->data=NULL;
//uso do nó sentinela: pressupõe que a lista nunca estará vazia, o first nunca será nulo.
    trashNode->previous=trashNode;
    trashNode->next=trashNode;
    list->first=trashNode;
    list->size=0;
}
// Insere novo elemento a lista.
int enqueue(DoublyLinkedList *list, void *data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	if (newNode==NULL) return -1;
	// caso nao haja espaço na memória informa ao usuario
	newNode -> data= data; // o novo nó aponta para a data
	newNode -> next = list -> first; //o novo nó avança e a lista aponta para o primeiro
	newNode -> previous = list -> first -> previous;
	// o novo nó aponta para anterior e a lista aponta para o primeiro que aponta para o anterior
	list -> first ->previous ->next = newNode;
	list -> first -> previous = newNode;
	// o ultimo nó aponta para o novo nó;
	list -> size++; // incrementa a quantidade de elementos na lista
	return 1;
}
// Remove o primeiro elemento da lista, caso a lista possua elementos.
void* dequeue(DoublyLinkedList *list) {
    if (isEmpty(list)) return NULL;   //Informação caso não haja elementos na lista
	Node *trash = list->first;
  	Node *first = list->first->next;
	first->next->previous = trash;
    trash->next = first->next;
    void *data = first->data;        //Informação do nó ser removida.
    free(first);     //Libera a memoria
    list->size--;     //Reduz a quantidade de elementos presentes na lista
    return data;     //Retorna o elemento removido
}
//Retorna o primeiro elemento da lista.
void* first(DoublyLinkedList *list) {
    return list->first->next->data;
}
//Retorna o endereço do ultimo nó.
void* last(DoublyLinkedList *list) {
    return list->first->previous->data;
}
//Insere o elemento no inicio da lista.
int push(DoublyLinkedList *list, void *data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;
    newNode->next = list->first->next; //novo nó que recebe list, first, next
    newNode->previous = list->first; //previous que recebe list,first que esta apontando para o inicio
    list->first->next->previous = newNode; // recebe o novo nó
    list->first->next = newNode;
    list->size++;
    return 1;
}
//Retorna primeiro elemento da lista
void* pop (DoublyLinkedList *list) {
	return dequeue(list);
}
void* top (DoublyLinkedList *list){
	return first (list);
}
//Verifica se a lista está vazia
bool isEmpty(DoublyLinkedList *list) {
	return (list -> size==0);
}
int indexOf(DoublyLinkedList *list,void *data,compare equal) {
    if (isEmpty(list)) return -1;
    int count=0;
    Node *aux = list->first->next;
    while(aux!=list->first && !equal(aux->data,data)) {
        aux=aux->next;
        count++;
    }
    return (aux==list->first)?-1:count;
}
//Localiza um nó em uma posição
Node* getNodeByPos(DoublyLinkedList *list,int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;

//Ponteiro que indica o primeiro nó da função 
    Node *aux = list->first->next;
//Busca pelo nó até o último elemento da lista ou a localização da posição.
    for (int count=0;(aux!=list->first && count<pos);count++,aux=aux->next);
    return aux;
}
// Retorna o elemento armazenado dada sua posição na tabela
void* getPos(DoublyLinkedList *list,int pos) {
    Node *res = getNodeByPos(list,pos);
    return (res==NULL)?NULL:res->data;
}
int add(DoublyLinkedList *list, int pos, void *data) {
    Node *aux = getNodeByPos(list, pos);
    if (aux==NULL) return -2;
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;
    newNode->next = aux;
    newNode->previous = aux->previous;
    aux->previous->next = newNode;
    aux->previous = newNode;
    list->size++;
    return 1;
}

int addAll(DoublyLinkedList *listDest, int pos, DoublyLinkedList *listSource) {
    Node *aux = getNodeByPos(listDest, pos);
    if (aux==NULL) return -2;
    if (isEmpty(listSource)) return -1;
    listSource->first->previous->next = aux;
    listSource->first->next->previous = aux->previous;
    aux->previous->next = listSource->first->next;
    aux->previous = listSource->first->previous;
    listDest->size+=listSource->size;
    return listSource->size;
}
//Remove um elemento de uma determinada posição
void* removePos(DoublyLinkedList *list, int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL; 
    Node *nodeRemove = getNodeByPos(list, pos);
//Auxiliar que recebe a posição
    nodeRemove->previous->next = nodeRemove->next;
// Navegação entre os nós
    nodeRemove->next->previous = nodeRemove->previous; // Atribui o valor de previous para o privious do próximo nó.
    void* dataRemove = nodeRemove->data;
    free(nodeRemove);
    list->size--;
    return dataRemove;
}
int removeData(DoublyLinkedList *list, void *data, compare equal) {
    if (isEmpty(list)) return -1;
    Node *nodeRemove = list->first->next;
    while(nodeRemove!=list->first && !equal(nodeRemove->data,data))
        nodeRemove=nodeRemove->next;
    if (nodeRemove!=list->first) {
        nodeRemove->previous->next = nodeRemove->next;
        nodeRemove->next->previous = nodeRemove->previous;
        free(nodeRemove->data);
        free(nodeRemove);
        list->size--;
        return 1;
    } else {
        return 0;
    }
}
//Exibe os dados de todos os nós da lista;
void show(DoublyLinkedList *list, printNode print) {
    Node *aux = list->first->next;
    while (aux!=list->first) {
        print(aux->data);
        aux=aux->next;
    }
    printf("\n");
}
// Mostra a estrutura de memória da lista duplamente ligada
void showMem(DoublyLinkedList *list) {
    printf("Trash Node: %p\n\n",list->first);
    Node *aux = list->first->next;
    printf("Node Addr  : Previous    - Data        - Next\n\n");
    while (aux!=list->first) {
        printf("%p: %p - %p - %p\n",aux, aux->previous, aux->data, aux->next);
        aux=aux->next;
    }
}