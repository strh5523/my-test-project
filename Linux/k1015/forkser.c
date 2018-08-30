#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>

/*void *fun(void *arg)
{
	int c = (int)arg;

	while(1)
	{
		char buff[128] = {0};
		if(recv(c,buff,127,0) <= 0)
		{
			break;
		}
		printf("read(%d)=%s\n",c,buff);
		send(c,"ok",2,0);
	}
	close(c);
	printf("one clinet close%d\n",c);
}*/
int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr,caddr;
	memset(&saddr,0,sizeof(saddr));//清空
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert( res != -1);
	
	listen(sockfd,5);

	while(1)
	{
		int len = sizeof(caddr);
		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c<0)
		{
			continue;
		}
		printf("accept c =%d,ip:%s,port:%d\n",c,inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
		pid_t pid = fork();
		assert(pid != -1);
		if(pid == 0)
		{

		while(1)
		{
			char buff[128] = {0};
			if(recv(c,buff,127,0) <= 0)
			{
				break;
			}
			printf("read(%d)=%s\n",c,buff);
			send(c,"ok",2,0);
		}
			close(c);
		}
		//pthread_t id;
		printf("one clinet close%d\n",c);
		//pthread_create(&id,NULL,fun,(void*)c);
		
	}
	
	
}
