#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

int main() {
    HashStruct hashes;
    Palavra t_palavra;
    initHash(&hashes);
    printf("\nTabela MAX %d iniciada com sucesso!",MAX);
    carregaArquivo(&hashes,&t_palavra);
    int opc;
    while (1)
    {
        printf(" \n\n::::::::::::::::::::: TABELA HASH MAX %d (%d x %d):::::::::::::::::::::\n\n\n",MAX,raiz_Qd(),raiz_Qd());
        printf("  \t[1] - IMPRIMIR LISTA\n\n");
        printf("  \t[2] - EXIBIR PORCENTAGEM DE OCUPACAO\n\n");
        printf("  \t[3] - EXIBIR POSICAO DAS COLISOES\n\n");
        printf("  \t[4] - MAPA DE ESPALHAMENTO\n\n");
        printf("  \t[0] - SAIR\n\n");
        printf("\n::::::Entre com uma opcao >>>> ");
        scanf ("%d",&opc);
        if (!opc) break;
        switch(opc)
        {
            case 1:
                showHashStruct(&hashes,printPalavra);
                break;
            case 2: //Calcula a porcentagem de ocupacao da tabela
                porcentagemHash(&hashes);
                break;
            case 3:
                imprimeColisoes(&hashes,printPalavra);
                break;
            case 4:
                mapaEspalhamento(&hashes);
                break;
            case 0:
                break;
            default:
                printf("\n\n Opcao invalida!!!\n\n");
                break;
        }
    }
    printf("\n\n ******** Programa finalizado pelo usuario!!! ********\n\n\n");
    return 0;
}
