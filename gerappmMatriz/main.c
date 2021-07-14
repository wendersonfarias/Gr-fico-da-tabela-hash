#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const int dimx = 3, dimy = 3;//Dimensão da matriz
    int i, j;
    int aux=2;
    FILE *fp = fopen("first.ppm", "wb"); /* b - modo binário */
    //Descrição do arquivo
    fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    //Varre a matriz em coloca uma cor na posição
    for (i = 0; i < dimy; ++i)
    {
        for (j = 0; j < dimx; ++j)
        {
            //tente trocar o unsigned char por outros tipos
            //Verifique o que significa unsigned char
            unsigned char color[3]={0};
            //unsigned char pix[]={0,10,0, 0,20,0, 0,30,0, 0,40,0, 0,50,0, 0,60,0};
            //color[0] = i+9*j % 256;  /* red */
            //color[1] = i % 256;  /* green */
            color[1] = aux;  /* green */
            aux=aux*2;
            //aux+=aux;
            //color[2] = (i+j) % 256;  /* blue */
            fwrite(color, 1, 3, fp);//Escreve no arquivo a cor
        }
    }
    fclose(fp);//Salva o arquivo
    return EXIT_SUCCESS;
}
