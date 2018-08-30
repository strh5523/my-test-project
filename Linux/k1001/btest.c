#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/msg.h>
#include<pthread.h>
#include<semaphore.h>
#include"list.h"

sem_t sem;
pthread_mutex_t mutex;
node head;


#define MAX 3

struct mess
{
	long type;
	int data;
};

void* fun(void * arg)
{
	int index = (int)arg;
	while(1)
	{
		sem_wait(&sem);

		pthread_mutex_lock(&mutex);
		int val = list_getelem(&head);
		pthread_mutex_unlock(&mutex);
		printf("thread[%d]   val=%d\n",index,val);
	}
	//p
	////lock
	//list_get();
	//unlock
}

int main()
{
	int msgid = msgget((key_t)1234,IPC_CREAT|0600);
	assert( msgid != -1);
	
	struct mess dt;

	sem_init(&sem,0,0);
	pthread_mutex_init(&mutex,NULL);
	list_init(&head);

	pthread_t id[MAX];

	int i = 0;
	for(;i<MAX;i++)
	{
		pthread_create(&id[i],NULL,fun,(void*)i);
	}

	while(1)
	{
		msgrcv(msgid,&dt,4,1,0);//0是不区分，1是第一个消息
		//printf("data=%d\n",dt.data);
		//lock
		pthread_mutex_lock(&mutex);
		list_insert(&head,dt.data);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem);
		//list_add();
		//unlock
		//v

	}
}
