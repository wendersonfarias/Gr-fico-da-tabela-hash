#include <stdio.h>
#include <stdlib.h>

int main(){
   FILE *imageFile;
   int x,y,pixel,height=4,width=4;

   imageFile=fopen("imagem.ppm","wb");
   if(imageFile==NULL){
      perror("ERROR: Cannot open output file");
      exit(EXIT_FAILURE);
   }

   fprintf(imageFile,"P6\n");               // P6 filetype
   fprintf(imageFile,"%d %d\n",width,height);   // dimensions
   fprintf(imageFile,"255\n");              // Max pixel

   unsigned char pix[]={
0,90,0,
 0,45,0,
 0,30,0,
 0,240,0,
 0,21,0,
 0,99,0};
   fwrite(pix,1,18,imageFile);
   fclose(imageFile);
}

for (j = 0; j < dimx; ++j)
        {
            unsigned char color[3]={0};
            //unsigned char pix[]={0,10,0, 0,20,0, 0,30,0, 0,40,0, 0,50,0, 0,60,0};
            color[1] = aux;  /* green */
            aux=aux*2;
            //aux+=aux;
            fwrite(color, 1, 3, fp);//Escreve no arquivo a cor
        }

255 = .
80 = x


