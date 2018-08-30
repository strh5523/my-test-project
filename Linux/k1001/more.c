#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>


sem_t sem;
#define MAX 5
int g = 0;
void * fun(void* arg)
{
	//int a = *(int*)arg;
	int i = 0;
	for(;i<1000;i++)
	{
		sem_wait(&sem);
		printf("fun run g=%d\n",g++);
		sem_post(&sem);
	}
	pthread_exit("fun over\n");
}
int main()
{

	pthread_t id[MAX];
	sem_init(&sem,0,1);
	int i = 0;
	for(;i<MAX;i++)
	{
		pthread_create(&id[i],NULL,fun,NULL);
	}
	for(i=0;i<MAX;i++)
	{
		pthread_join(id[i],NULL);
	}

}
