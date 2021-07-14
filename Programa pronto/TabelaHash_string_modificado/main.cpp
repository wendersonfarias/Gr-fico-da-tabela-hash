# include "hash.c"

main(){
    Hash tab;
    int num, elemento, op,cont = 0, conti = 0;
    FILE* arquivo;

    while(num != 8) {
        menuHash(&num);
        switch(num){
            case 1:
                if(cont > 0){
                    system("cls");
                    printf("\nTabela ja inicializada!!\n");
                }else{
                cont++;
                inicializaHash(tab);
                //mensagem();
                }
                break;
            case 2:
                if(cont > 0){
                    conti++;
                    carregaArquivo(tab);
                }else{
                    mensagem3();
                }
                break;
            case 3:
                if(conti > 0){
                    system("cls");
                    lerNumero(&elemento);
                    buscaHash(tab,elemento);
                    getchar();
                }else{
                    mensagem4();
                }
                break;
            case 4:
                if(conti > 0){
                    system("cls");
                    lerNumero1(&elemento);
                    removeHash(tab,elemento);
                    getchar();
                }else{
                    mensagem4();
                }
                break;
            case 5:
                if(conti > 0){
                    system("cls");
                    imprimeHash(tab);
                }else{
                    mensagem4();
                }
                getchar();
                break;
            case 6:
                op = -1;
                if(conti > 0){
                while(op != 0){
                    menuEstatistica(&op);
                    switch(op){
                        case 0:
                            system("cls");
                            break;
                        case 1:
                            system("cls");
                            posicao(25,3);printf("%g%% da tabela foi preenchida!\n",porcentagemHash(tab));
                            getchar();
                            break;
                        case 2:
                            system("cls");
                            indiceColisao(tab);
                            getchar();
                            break;
                        case 3:
                            system("cls");
                            lerNumero2(&op);
                            imprimeColisao(tab,op);
                            getchar();
                            break;
                        case 4:
                            system("cls");
                            posicao(25,3);printf("Total de colisoes = %d",quantidadeColisao(tab));
                            getchar();
                            break;
                        case 5:
                            system("cls");
                            posicoesVazias(tab);
                            getchar();
                            break;
                        default:
                            system("cls");
                            printf("\nOpcao invalida!");
                            getchar();
                            break;
                        }
                        system("cls");
                    }
                }else{
                    mensagem4();
                }
                    break;
                case 7:
                    exit(0);
                    default:
                    system("cls");
                    printf("\nOpcao invalida!\n");
                    getchar();
                    break;
        }
        system("cls");
    }
}


