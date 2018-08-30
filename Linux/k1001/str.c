#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<pthread.h>

void * fun(void* fun)
{
	char str[] = "a b c d e r t y u i";
	char *q = NULL;
	char *p = strtok_r(str," ",&q);
	printf("fun p=%s\n",p);
	sleep(1);
	while((p = strtok_r(NULL," ",&q)) != NULL)
	{
		printf("fun p=%s\n",p);
		sleep(1);
	}
	

}
int main()
{
	pthread_t id;
	pthread_create(&id,NULL,fun,NULL);
	char a[] = {"1 2 3 4 5 6 7 8 9 10"};
	char *q = NULL;
	char * s = strtok_r(a," ",&q);
	printf("main s=%s\n",s);
	sleep(1);
	while((s = strtok_r(NULL," ",&q)) != NULL)
	{
		printf("main s=%s\n",s);
		sleep(1);
	}
	pthread_join(id,NULL);
}
