#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);//ipv4,tcp
	assert(sockfd != -1);

	struct sockaddr_in saddr,caddr;//专用的地址结构
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);//端口0～1024管理员使用  知名端口  1024～4096保留端口 4096～+临时端口
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));

	listen(sockfd,5);

	while(1)
	{
		int len = sizeof(caddr);
		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c < 0)
		{
			continue;
		}
		pid_t pid = fork();
		assert(pid != -1);
		if(pid == 0)
		{
			char buff[128] = {0};
			int n = recv(c,buff,127,0);
			printf("accep c=%d\n",c);
			printf("n=%d,buff=%s",n,buff);
		}
		send(c,"ok",2,0);

		close(c);
	}
}
