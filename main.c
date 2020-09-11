#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
int rA=3 , cA=2 , rB=2 ,cB=3;
int matrixA[3][2]={{1,2},{8,3},{5,6}};
int matrixB[2][3]={{3,4,5},{7,2,1}};

typedef struct arg_struct {
    int **matrixC;
    int index;

}arg;

void nonThreadedMatMult(int matrixC[][cB]){

int i,j,k,c,d;
int sum=0;
     for(i=0;i<rA;i++)
        {
            for(j=0;j<cB;j++)
            {
                for(k=0;k<cA;k++)
                {

                    sum+=matrixA[i][k]*matrixB[k][j];
              }
              matrixC[i][j]=sum;
              sum=0;
            }
        }

  for (c = 0; c < 3; c++) {
      for (d = 0; d < 3; d++)
        printf("%d\t", matrixC[c][d]);

      printf("\n");
    }

}

void *calculateRow(void *param){
   int k,j,d;
   int sum=0;
 arg *args=(arg *)param;
for(k=0;k<cB;k++)
{
 for(j=0;j<rB;j++)
            {

           sum+=matrixA[args->index][j]*matrixB[j][k];
            }
            args->matrixC[args->index][k]=sum;
sum=0;
}
   //for (d = 0; d < 3; d++)
       // printf("%d\t",  args->matrixC[index][d]);
        pthread_exit(0);
}

void threadedMatMultPerRow(int matrixC[][cB]){
pthread_t threads[rA];
arg *args;

    int i;
    for(i=0;i<rA;i++){
    args[i]=(arg){
.index=i,
.matrixC=matrixC};
       pthread_create(&threads[i],NULL,(void*)calculateRow ,(void*)&args[i]);

    }
 for(i=0;i<rA;i++){
        pthread_join(threads[i],NULL);

 }

}

int main()
{
   if(cA!=rB)
    {
        printf("Multipication of Matrix not Possible !!!");
    }
   int result[3][3];
nonThreadedMatMult(result);

    return 0;
}
