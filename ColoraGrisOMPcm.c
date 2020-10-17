#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 12

int main()
{
    FILE *image, *outputImage, *lecturas;
    unsigned char* imgIni = (unsigned char*)malloc(226241*3*sizeof(unsigned char));
    unsigned char* imgRes = (unsigned char*)malloc(226241*3*sizeof(unsigned char));
    image = fopen("flores.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img22_dd.bmp","wb");    //Imagen transformada
    unsigned char r, g, b;               //Pixel
    int j =0;
    
    for(int i=0; i<54; i++) fputc(fgetc(image),outputImage);

    while(!feof(image)){
        *(imgIni+j)=fgetc(image);
        j++;
    } //copia adtos de imagen a al apuntador imgIni
        
     #pragma omp parallel
    {
     #pragma omp for ordered
        for (int i =0; i<226241*3; i+=3){
            b = *(imgIni+i);
            g = *(imgIni+i+1);
            r = *(imgIni+i+2);
            
            unsigned char pixel = 0.21*r+0.72*g+0.07*b;
            
            #pragma omp ordered
            {
                *(imgRes+i)=pixel; //b
                *(imgRes+i+1)=pixel;//g
                *(imgRes+i+2)=pixel;//r
            }
        }
            

    }
    for (int i=0; i< 226241*3; i++){
        
        fputc(*(imgRes + i), outputImage);
    }

    free(imgIni);
    free(imgRes);
    fclose(image);
    fclose(outputImage);
    return 0;
}
