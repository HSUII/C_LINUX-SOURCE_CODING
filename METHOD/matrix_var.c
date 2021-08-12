//프로그램실행시 행렬의 크기를 받아 출력하는 랜덤하게 출력하는 함수 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#define MAX_LEN 1000

void print_matrix(int**,char* name,int len);


int main(int argc,char** argv){

        int **a;
        int **b;
        int **c;
        int i,j,k;
        int len;
        clock_t start,stop;

        if(argc == 2){
                len=atoi(argv[1]);
        }else
        {
                len=10;
        }
        a=(int**)malloc(len * sizeof(int*));
        b=(int**)malloc(len * sizeof(int*));
        c=(int**)malloc(len * sizeof(int*));


        for(i=0;i<len;i++){

                        a[i]=(int*)malloc(len * sizeof(int*));
                        b[i]=(int*)malloc(len * sizeof(int*));
                        c[i]=(int*)malloc(len * sizeof(int*));

        }

        srandom((unsigned int)time(NULL));
        for(i=0;i<len;i++){
                        for(j=0;j<len;j++){
                                        a[i][j]=(random()%10);
                                        b[i][j]=(random()%10);
                        }
        }
        start=clock();
        mat_mul(a,b,c,len);
        stop = clock();

        print_matrix(a,"A",len);
        print_matrix(b,"B",len);
        print_matrix(c,"C",len);

        printf("processing time : %f\n",((double)stop-start)/CLOCKS_PER_SEC);
        return 0;
}

int mat_mul(int** a,int** b,int** c,int len){
        int i,j,k;
                for(i=0;i<len;i++){
                        for(j=0;j<len;j++){
                                //c[i][k]=a[i][j]+b[i][j] = add matrix
                                c[i][j]=0;
                                for(k=0;k<len;k++){
                                        c[i][j]+=a[i][k]*b[k][j];
                                }
                        }
        }
}

int mat_inv(int** src,int** dst,int len){
/*
        int i,j,k;
                for(i=0;i<len;i++){
                        for(j=0;j<len;j++){
                                //c[i][k]=a[i][j]+b[i][j] = add matrix
                                dst[i][j]=0;
                                for(k=0;k<len;k++){
                                        dst[i][j]+=src1[i][k]*src2[k][j];
                                }
                        }
        }
        */
}

void print_matrix(int** matrix, char* name,int len)
{
        int i,j;
        printf("======== %s matrix ========\n",name);
        for(i=0;i<len;i++){
                        for(j=0;j<len;j++){
                                printf("%d ",matrix[i][j]);
                        }
                        printf("\n");
        }

}
