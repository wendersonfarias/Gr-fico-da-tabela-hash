#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

int main() {
    HashStruct hashes;
    Palavra t_palavra;
    initHash(&hashes);
    int opc;
    while (1)
    {
        printf(" \n\n::::::::::::::::::::: MENU :::::::::::::::::::::\n\n\n");
        printf("  \t[1] - INICIAR TABELA\n\n");
        printf("  \t[2] - LER ARQUIVO TXT\n\n");
        printf("  \t[3] - IMPRIMIR LISTA\n\n");
        printf("  \t[4] - EXIBIR PORCENTAGEM DE OCUPACAO\n\n");
        printf("  \t[5] - EXIBIR COLISOES\n\n");
        printf("  \t[6] - MAPA DE COLISOES\n\n");
        printf("  \t[0] - SAIR\n\n");
        printf("\n\n::::::Entre com uma opcao >>>> ");
        scanf ("%d",&opc);
        if (!opc) break;
        switch(opc)
        {
            case 1:
                //initHash(&hashes);
                break;
            case 2://Abre o arquivo, faz a leitura e grava na tabela
                carregaArquivo(&hashes,&t_palavra);
                break;
            case 3:
                showHashStruct(&hashes, printPalavra);

                break;
             case 4: //Calcula a porcentagem de ocupacao da tabela
                {
                    porcentagemHash(&hashes);
                }
                break;
             case 5:
                imprimeColisoes(&hashes, printPalavra);
                break;
            case 6:
                mapaColisoes(&hashes);
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
