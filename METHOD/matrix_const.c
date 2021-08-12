//정해진 크기 배열 출력 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 10

void print_matrix(int [][MAX_LEN],char* name);


int main(){

        int a[MAX_LEN][MAX_LEN];
        int b[MAX_LEN][MAX_LEN];
        int c[MAX_LEN][MAX_LEN];

        int i,j,k;
        /*
        a[0][0] =1;
        a[0][1] =1;
        a[1][0] =1;
        a[1][1] =1;
        b[0][0] =1;
        b[0][1] =1;
        b[1][0] =1;
        b[1][1] =1;
        */

        srandom((unsigned int)time(NULL));
        for(i=0;i<MAX_LEN;i++){
                        for(j=0;j<MAX_LEN;j++){
                                        a[i][j]=(random()%10);
                                        b[i][j]=(random()%10);
                        }
        }
        for(i=0;i<MAX_LEN;i++){
                        for(j=0;j<MAX_LEN;j++){
                                //c[i][k]=a[i][j]+b[i][j] = add matrix
                                c[i][j]=0;
                                for(k=0;k<MAX_LEN;k++){
                                        c[i][j]+=a[i][k]*b[k][j];
                                }
                        }
        }
        print_matrix(a,"A");
        print_matrix(b,"B");
        print_matrix(c,"C");

        return 0;
}

void print_matrix(int matrix[][MAX_LEN], char* name)
{
        int i,j;
        printf("======== %s matrix ========\n",name);
        for(i=0;i<MAX_LEN;i++){
                        for(j=0;j<MAX_LEN;j++){
                                printf("%d ",matrix[i][j]);
                        }
                        printf("\n");
        }




}
