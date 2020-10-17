#include <stdio.h>
#include <omp.h>



FILE* fptr;

int main(int argc, char const *argv[]){
    fptr = fopen("ResultadoMultiplicación","w");
    float A[100][100];
    float B[100][100];
    float C[100][100];             //nueva matriz nxn
    int i,j,k;
    double t1,t2,tiempo;
    int n= 100;

    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            A[i][j]=j;
        }
    }
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            B[i][j]=j;
        }
    }
t1=omp_get_wtime();

  {
    for (int i=0;i<n-1;i+=3){
        for (int j=0;j<n;j++){
        C[i][j]=0;
        for (int k=0;k<n;k++){
            C[i][j]=C[i][j]+ (A[i][k]*B[k][j]);
        }
        }
        for (int j=0;j<n;j++){
        C[i+1][j]=0;
        for (int k=0;k<n;k++){
            C[i+1][j]=C[i+1][j]+ (A[i+1][k]*B[k][j]);
        }
        }
        for (int j=0;j<n;j++){
        C[i+2][j]=0;
        for (int k=0;k<n;k++){
            C[i+2][j]=C[i+2][j]+ (A[i+2][k]*B[k][j]);
        }
        }
        
    }
    
    
         for (int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    fprintf(fptr,"%f\t", C[i][j]);
                }
             fprintf(fptr,"\n");
         }
    }
        t2=omp_get_wtime();
        tiempo= t2-t1;
       
       
        printf("tiempo:%f\n", tiempo);
        fclose(fptr);
        return 0;
        
}
