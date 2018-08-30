#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>


sem_t sem;
pthread_mutex_t mutex;
void* fun(void* fun)
{
	

	int i = 10;
	while(i)
	{
		sem_wait(&sem);
		//pthread_mutex_lock(&mutex);
		write(1,"A",1);
		sleep(2);
		write(1,"A",1);
		sem_post(&sem);
		//pthread_mutex_unlock(&mutex);
		sleep(2);
		i--;
	}
}

int main()
{
	pthread_t id;
	pthread_create(&id,NULL,fun,NULL);

	sem_init(&sem,0,1);
	int i = 10;
	while(i)
	{
		//pthread_mutex_lock(&mutex);
		sem_wait(&sem);
		write(1,"B",1);
		sleep(2);
		write(1,"B",1);
		sem_post(&sem);
		//pthread_mutex_unlock(&mutex);
		sleep(2);
		i--;
	}



	pthread_join(id,NULL);
	
	//pthread_mutex_trylock(&mutex);
}
