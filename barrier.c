#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

pthread_barrier_t pbar;
void* p1()
{
  pthread_barrier_wait (&pbar);
printf("\nthread t1 started\n");
}
void * p2(){
 pthread_barrier_wait (&pbar);
printf("\nthread t2 started\n");
}

void* p3(){
 pthread_barrier_wait (&pbar);
printf("\n thread t3 started");
}
void* p4(){
pthread_barrier_wait (&pbar);
printf("\n thread t4 started\n");
exit(0);
}

int main(){
pthread_barrier_init(&pbar,NULL,4);
void* (*tid[4])();
tid[0]=p1;
tid[1]=p2;
tid[2]=p3;
tid[3]=p4;
pthread_t thrid[3];
//for (int i=3;i>=0;i++){
//pthread_create(&thrid[i],NULL,tid[i],NULL);
//}
pthread_create(&thrid[0],NULL,p4,NULL);
sleep(2);
pthread_create(&thrid[1],NULL,p2,NULL);
sleep(2);
pthread_create(&thrid[2],NULL,p3,NULL);
sleep(2);
pthread_create(&thrid[3],NULL,p1,NULL);
sleep(2);
while(1);
}
