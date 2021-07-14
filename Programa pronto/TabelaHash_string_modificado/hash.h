#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#define NPAL 50 /* dimensão máxima de cada palavra */
#define NTAB 100 /* dimensão da tabela de dispersão */

/*hash.h armazena a estrutura e os prototipos das funcaoes*/
struct dados{
    int info;
    char pal[NPAL];
    struct dados *prox;
};
typedef struct dados Dados;
typedef Dados* Hash[NTAB];
int funcaoHash(char* s);
void inicializaHash(Hash tab);
void insereHash(Hash tab,char* s,int num);
void buscaHash(Hash tab, int num);
void imprimeHash(Hash tab);
void removeHash(Hash tab, int num);
int carreagaArquivo(Hash tab);
void linhaAnimada(int q, int a);
void linha(int q, int a);
void cor(WORD cor);
void posicao(int x, int y);
void menuHash(int *num);
void menuEstatistica(int *num);
float porcentagemHash(Hash tab);
void indiceColisao(Hash tab);
int quantidadeColisao(Hash tab);
void posicoesVazias(Hash tab);
void imprimeColisao(Hash tab, int pos);
void lerNumero(int *num);
void lerNumero1(int *num);
void lerNumero2(int *num);
void mensagem();
void mesagem2();
void mensagem3();
void mensagem4();

#endif // HASH_H_INCLUDED
