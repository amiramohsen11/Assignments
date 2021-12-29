#include<stdio.h>
#include<pthread.h>

int array[100];
void *sum(void *arg)
{
int summ=0;
  int start=(int ) arg;
  for(int i=start;i<(start+10);i++)
   {
     summ=summ+array[i];
   }
   return (void*)summ;
}



int main()
{
 
    for(int i=0;i<100;i++)
   {
      array[i]=(i+1)*5;
    
    }

pthread_t tid[10];

for (int k=0;k<10;k++)
{
  pthread_create(&tid[k],NULL,sum,(void*)(k*10));
}
void *collect;

int summ2=0;

for(int s=0;s<10;s++)
{
	pthread_join(tid[s],&collect);
	summ2=summ2+(int)collect;
}

printf("SUM OF NUMBERS IS : %d",summ2);
printf("\n");
return 0;
}
