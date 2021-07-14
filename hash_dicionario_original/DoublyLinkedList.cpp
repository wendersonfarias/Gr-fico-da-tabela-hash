#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"

//Alguns pontos e diferen�as da Lista Duplamente Ligada X Lista Simplesmente Ligada
//Agora na Lista Duplamente Ligada temos dois ponteiros: next e previous
//Lista Duplamente Ligada permite a navega��o nos dois sentidos, ela ocupa mais mem�ria que a anterior (Lista Simplesmente Ligada)
//Essa Lista Duplamente Ligada ser� feita no formato circular, por isso, diferente da Lista Simplesmente ligada onde first: nulo  (list->first=NULL;) agora first: n� lixo  (list->first=trashNode;) recebe trashNode
//init ==> inicializa a DoublyLinkedList.h
void init(DoublyLinkedList *list) {
//trashNode: n� lixo, ou sentinela (permite que mesmo a lista estando vazia ela aponta para um n�: (list->first=trashNode;)
    Node *trashNode = (Node*)malloc(sizeof(Node));
    trashNode->data=NULL;
//uso do n� trash: pressup�e que a lista nunca vai estar� vazia, o first nunca ser� nulo
//Dito isso, diferentemente da Lista Simplesmente Ligada n�o precisamos verificar se a lista est� vazia
    trashNode->previous=trashNode;
    trashNode->next=trashNode;
    list->first=trashNode;
    list->size=0;
}

// enqueue by Matheus Santiago, semelhante a lista ligada, este enqueue tem a fun��o de inserir um novo elemento respeitando o conceito de fila.
int enqueue(DoublyLinkedList *list, void *data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	if (newNode==NULL) return -1;
	// caso nao haja espa�o informa ao usuario

	newNode -> data= data; // o novo n� aponta para a data
	newNode -> next = list -> first; //o novo n� avan�a e a lista aponta para o primeiro
	newNode -> previous = list -> first -> previous;
	// o novo n� aponta para anterior e a lista aponta para o primeiro que aponta para o anterior
	list -> first ->previous ->next = newNode;
	list -> first -> previous = newNode;
	// o ultimo n� aponta para o novo n�;

	list -> size++; // incrementa a quantidade de elementos na lista
	return 1;
}

// Dequeue (by Carlos Henrique T. Carneiro) Fun��o com objetivo de remover o primeiro elemento da lista, se a lista possuir elementos.
void* dequeue(DoublyLinkedList *list) {
    if (isEmpty(list)) return NULL;   //Retorna valor vazio caso a lista n�o possua elementos
	Node *trash = list->first;
  	Node *first = list->first->next;

	first->next->previous = trash;
    trash->next = first->next;

    void *data = first->data;        //dado do n� a ser removido

    free(first);     //Libera a memoria
    list->size--;     //Reduz a quantidade de elementos presentes na lista
    return data;     //Retorna o elemento removido
}

//first (by Gabriel Robert) descobre qual o primeiro dado da lista.
void* first(DoublyLinkedList *list) {
    return list->first->next->data;
//assim como na "lista simplesmente ligada" o "first" retorna o endere�o de mem�ria do dado no primeiro n�,
//por�m n�o contem mais a fun��o "(isEmpty(list))?NULL" para retornar NULL se o endere�o estiver Vazio.
}

//last (by Jos� Guilherme Neves), tem a mesma fun�ao da lista simplesmente ligada, onde retorna o endere�o de memoria do ultimo n�
void* last(DoublyLinkedList *list) {
    return list->first->previous->data;
}


//Push por Vinicius Matusita, faz a inserna  inser��o do elemento no inicio como na simplesmente ligada, porem com mais 2 ponteiros.
int push(DoublyLinkedList *list, void *data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;

    newNode->next = list->first->next; //novo � que recebe list, first, next
    newNode->previous = list->first; //previous que recebe list,first que esta apontando para o inicio
    list->first->next->previous = newNode; // recebe o novo n�
    list->first->next = newNode;

    list->size++;

    return 1;
}
//top( by Thiago Ramalho) usado somente em pilha, retorna o elemento superior da pilha, ela possui duas fun��es, retornar o elemento para a parte superior da pilha para permitir modifica��es, a segunda fun��o � para retornar uma refer�ncia constante,com intuito de garantir que n�o haja modifica��es acidentaisna pilha.
void* pop (DoublyLinkedList *list) {
	return dequeue(list);
}
void* top (DoublyLinkedList *list){
	return first (list);
}
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
// GetNodeByPos por Lucio Lisboa, fun��o com o proposito de encontrar um n� em uma posi��o especifica da lista e retorna-lo. Fun��o identica a de LinkedList
Node* getNodeByPos(DoublyLinkedList *list,int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;
//condi��o para checar se a lista esta vazia ou se a posi��o desejada � superior ao tamanho da lista, caso qualquer uma seja verdadeira, retorna nulo

//gera uma copia do ponteiro que aponta o primeiro n� da fun��o na variavel aux
    Node *aux = list->first->next;
//estrutura de repeti��o que caminha do primeiro n� at� a posi��o desejada ou at� o ultimo n� da lista e retorna ele para a fun��o principal
    for (int count=0;(aux!=list->first && count<pos);count++,aux=aux->next);
    return aux;
}

// getpos por Alessandra Mirelle, tem a mesma fun��o que na simplesmente ligada, onde a fun��o retorna o dado e n�o o endere�o do n�.
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

//removePos (By Wallatan Fran�a)  remove um elemento de uma determinada posi��o
// cria uma fun��o do tipo vazio e ponteiro
void* removePos(DoublyLinkedList *list, int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL; //se a condi��o for atendida � retornado null
    Node *nodeRemove = getNodeByPos(list, pos);
//cria uma v�riavel auxiliar que vai receber um n� de uma posi��o da lista
    nodeRemove->previous->next = nodeRemove->next;
// NodeRemove recebe o pr�ximo n� a ele, e atribui ele como o valor do next do n� anterior a ele
    nodeRemove->next->previous = nodeRemove->previous; // Atribui o valor de previous para o privious do pr�ximo n�
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

//Exibe os dados de todos os n�s da lista;
void show(DoublyLinkedList *list, printNode print) {
    Node *aux = list->first->next;
    while (aux!=list->first) {
        print(aux->data);
        aux=aux->next;
    }
    printf("\n");
}
// Esta fun��o mostra a estrutura em mem�ria da lista duplamente ligada
void showMem(DoublyLinkedList *list) {
    printf("Trash Node: %p\n\n",list->first);
    Node *aux = list->first->next;
    printf("Node Addr  : Previous    - Data        - Next\n\n");
    while (aux!=list->first) {
        printf("%p: %p - %p - %p\n",aux, aux->previous, aux->data, aux->next);
        aux=aux->next;
    }
}
