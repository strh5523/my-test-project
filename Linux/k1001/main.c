#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
//int g = 10;
void * fun(void* arg)
{
	int a = *(int*)arg;
	int i = 0;
	for(;i<5;i++)
	{
		printf("fun run a=%d\n",a);
		sleep(1);
	}
	pthread_exit("fun over\n");
}
int main()
{
	int a = 100;
	pthread_t id;
	pthread_create(&id,NULL,fun,(void*)&a);

	int i = 0;
	for(;i<5;i++)
	{
		printf("main run a=%d\n",a++);
		sleep(1);
	}
	char* s = NULL;
	pthread_join(id,(void**)&s);
	printf("main: s=%s\n",s);
}
