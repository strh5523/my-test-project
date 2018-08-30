#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>


int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));//清空
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("192.168.31.120");

	int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert( res != -1);

	while(1)
	{
		char buff[128] = {0};
		printf("input:\n");

		fgets(buff,128,stdin);
		if(strncmp(buff,"end",3) == 0)
		{
			break;
		}

		send(sockfd,buff,strlen(buff),0);
		memset(buff,0,sizeof(buff));
		recv(sockfd,buff,127,0);

		printf("buf=%s\n",buff);
	}
	close(sockfd);
}
	
	
