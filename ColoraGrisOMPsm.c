#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 12

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("flores.bmp","rb");           //imagen original a transformar
    outputImage = fopen("img3_dd.bmp","wb");    //imagen transformada
    
    unsigned char r, g, b; //pixel
    
    for(int i=0; i<54; i++) fputc(fgetc(image), outputImage); //copia cabecera a nueva imagen
    
#pragma omp parallel
    {
    #pragma omp for schedule(guided)
        for (int i=0;i<226241;i++){
            
        b=fgetc(image);
        g=fgetc(image);
        r=fgetc(image);
        
        unsigned char pixel= 0.21*r + 0.72*g + 0.07*b;
        fputc(pixel, outputImage);
        fputc(pixel, outputImage);
        fputc(pixel, outputImage);
        }
    }
    
    fclose(image);
    fclose(outputImage);
    return 0;
}
