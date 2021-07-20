#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

//Função de inicialização para percorrer cada posição da tabela de hash inicializando a lista duplamente ligada
//Init usado é o da DoublyLinkedList, Lista Duplamente Ligada.
void initHash(HashStruct *hashStruct) {
    for (int i=0;i<MAX;i++) {
        //chamando init de DoublyLinkedList para inicializar cada lista do vetor
        init(&(hashStruct->hashes[i]));
    }
    hashStruct->size = 0;
}

// Recebe uma chave e calcula qual posição deveremos inserir o dado associado a chave.
int hash(char *key) {
    int sum = 0;
    //Percorre todos os caracteres da string passada
    for (int i = 0; key[i]!=0;i++) {
         //acumulamos os códigos ascii de cada letra com um peso
        sum+=key[i]*(i+1);
    }
    return sum%MAX;  //retorna o resto da divisão
}
/*
int hash(char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = c + (hash << 6) + (hash << 16) - hash;
        return hash % MAX;
}*/

//Booleano para verificar se a tabela está ou não vazia.
bool isHashEmpty(HashStruct *hashStruct) {
    return hashStruct->size==0;
}

// Verifica se a chave já está contida na tabela.
// Caso contrário, é inserido um novo elemento na tabela.
int put(HashStruct *hashStruct, char *key, void *data, compare equal)  {
	if (!containsKey(hashStruct, key, equal)){
        //Adiciona na fila que está na posição devolvida pela função hash
        int res = enqueue(&hashStruct->hashes[hash(key)],data);
        //Incrementa a quantidade de elementos baseado na quantidade inserida por enqueue
        hashStruct->size+=res;
        return res;
    }
    return 0;
}
// Verificar se a chave já existe na tabela de hash.
bool containsKey(HashStruct *hashStruct, char *key, compare equal) {
    //calcula a posição
    int hashValue = hash(key);//função para descobrir em que lista está a chave.
    //busca na fila a posição da chave
    int pos = indexOf(&hashStruct->hashes[hashValue], key, equal);
    //A função indexOf retorna a posição da chave na lista. Caso o retorno seja -1 a chave não está na lista.
    //printf("\n Posicao >>> %d \n",pos);
    return (pos!=-1)?true:false;
}
//Realiza busca no codigo e retorna o dado procurado, se não houverem dados retorna o primeiro nó (sentinela) de valor nulo.
void* get(HashStruct *hashStruct, char *key, compare equal) {
    // descobre em qual fila/lista está o dado
    int hashValue = hash(key);
    //first é nó sentinela, começamos do segundo nó
    Node *aux = hashStruct->hashes[hashValue].first->next;
    // procuramos o dado na lista
    while(aux!=hashStruct->hashes[hashValue].first && !equal(aux->data, key))
        aux=aux->next;
    return aux->data;
}
//Remove um par (chave, valor)
void* removeKey(HashStruct *hashStruct, char *key, compare equal) {
    int hashValue = hash(key);// após calcular o hash da chave enviada, atribui o valor a váriavel do tipo hashValue
    int pos = indexOf(&hashStruct->hashes[hashValue], key, equal);// a váriavel pos tipo int, recebe a posição encontrada por indexOf com base nos parâmetros passados
	//remove o valor da posição
    void* result = removePos(&hashStruct->hashes[hashValue], pos);
	//Verifica se é o unico nó da lista, se nao for, diminui um valor de size em 1
    if (result!=NULL) hashStruct->size--;
    return result;
}

//Exibe os pares armazenados, ou seja, mostra quantos hash tem e quantos elementos cada hash tem
void showHashStruct(HashStruct *hashStruct, printNode print) {
    //estrutura de repetição com o intuito de navegar entre as hashes e mostrar quantos elementos cada hash tem
    for (int i=0; i < MAX; i++) {
        printf("Hash %d tem %d elementos: ",i,hashStruct->hashes[i].size);
        show(&hashStruct->hashes[i],print);
        printf("\n");
    }
    //Exibe a quantidade de elementos a hash tem
    printf("\n\nForam inseridas %d palavras nesta tabela.\n\n",hashStruct->size);
}
//Faz a verificacao da igualdade dos dados. Por ser void, pode ser de qualquer tipo.
bool comparaChaves(void *key, void *data) {
    char *chave = (char*)key;
    Palavra *c = (Palavra*)data;
    return (strcmp (chave, c->texto) == 0)?true:false;
}
//Imprime o elemento armazenado
void printPalavra(void *data) {
    Palavra *palavra = (Palavra*)data;
    printf("{%s} - ", palavra->texto);
}
//Exibe as colisoes, caso elas existam
void imprimeColisoes(HashStruct *hashStruct, printNode print) {
    int cont=0;
    
    //Navega entre as hashes e mostrar quantos elementos cada hash tem
    printf("\n\t");
    for (int i=0; i < MAX; i++) 
        if ((hashStruct->hashes[i].size)>1){
            printf("%d\t",i);
            cont++;
        }
    //Exibe quantos elementos a hash tem
    printf("\n\n\nForam contabilizados %d elementos nesta tabela, tendo ocorrido",hashStruct->size);
    //Exibe a quantidade de ocorrencias das colisoes
    printf(" %d colisoes.",cont);
}
//Mostra a porcentagem de ocupacao da tabela
void porcentagemHash(HashStruct *hashStruct){
        float contador = 0.0;
        for (int i=0; i < MAX; i++) {
            if(hashStruct->hashes[i].size >= 1){//Caso a hash tenha pelo menos um elemento, o contador é incrementado.
                contador += 1;
            }
        }
    printf("\n A PORCENTAGEM DE OCUPACAO FOI DE %.2f%%", (contador/MAX)*100 );//Cálculo da porcentagem e apresentação para o usuário.
}
//Gera arquivo no formato PPM para visuzalização do espalhamento da hash.
void mapaEspalhamento(HashStruct *hashStruct){
    int var;//Variavel para receber a quantidade de elementos de cada lista.
    int dim_tab=raiz_Qd();
    FILE *imageFile;
    //int larg=55,alt=55;
    int larg=dim_tab;
    int alt=dim_tab;
    imageFile=fopen("imagem.ppm","wb");//Abertura do arquivo
    if(imageFile==NULL){
        perror("ERROR: Cannot open output file");
        exit(EXIT_FAILURE);
    }
    //Escreve o cabeçalho do formato PPM
    fprintf(imageFile,"P3\n");               // P3 filetype
    fprintf(imageFile,"%d %d\n",larg,alt);   // dimensão da imagem
    fprintf(imageFile,"255\n");              // Máximo de pixel
    for (int i=0; i < MAX; i++) {
        //Caso a lista não esteja vazia, é escrito no PPM uma variação de cor conforme a quantidade de elementos.
        if ((hashStruct->hashes[i].size)!= 0){  
            if ((hashStruct->hashes[i].size) >= 1){
                var=255/(hashStruct->hashes[i].size);
                fprintf(imageFile,"0 %d 0\n",var);//Impressão da variação de cor.
            }
        }else//Caso a posição da hash esteja vazia, imprima a cor mais clara possível.
            fprintf(imageFile,"241 255 162\n");
    }
    printf("\n\nArquivo PPM gerado com sucesso. Visualize o arquivo na pasta de execucao deste programa.");
    fclose(imageFile);
}
//Carrega o arquivo de texto para alimentar a tabela hash
void carregaArquivo(HashStruct *hashStruct,Palavra *t_palavra){
    Palavra *c = (Palavra *)malloc(sizeof(Palavra));
    char url[]="lista.txt";//guarda o nome do arquivo
    FILE *arq;
    arq = fopen(url, "r");//Abertura do arquivo
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while(!feof(arq)){//Até o final do arquivo 
            c = (Palavra *)malloc(sizeof(Palavra));//Cria um espaço na memória para armazena a palavra
            fscanf(arq, "%s", c->texto);//Leia a palavra e armazene na variável auxiliar
            put(hashStruct, c->texto, c, comparaChaves);//Faça o empilhamento da palavra na tabela
        }
        printf("\nArquivo carregado com sucesso!");
        fclose(arq);//O arquivo é fechado
}
int raiz_Qd(){
    int n;
    float recorre = MAX;
   
    for (n = 0; n < 10; ++n)
          recorre = recorre/2 + MAX/(2*recorre);
           
    return(recorre);    
}    

