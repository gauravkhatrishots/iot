#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<strings.h>
#include<unistd.h>

sem_t  psem;
sem_t  rsem;
int pd[2];
void* print  ()
{
int i;
while(1){
sem_wait(&psem);
printf("(you are in write thread) you entered  :");
read(pd[0],&i,sizeof(int));
printf("%d",i);
sem_post(&rsem);
}
}

void* input ()
{int i;
while(1){
sem_wait(&rsem);
printf("\n(you are in read thread) enter a number ");
scanf("%d",&i);
write(pd[1],&i,sizeof(int));
sem_post(&psem);
}
}

int main()
{
int psemid,rsemid;
pipe(pd);
rsemid=sem_init(&rsem,0,1);
psemid=sem_init(&psem,0,0);
pthread_t prid,rdid;
pthread_create( &prid ,NULL,print,NULL);
pthread_create(&rdid,NULL,input,NULL);
while(1);
}

