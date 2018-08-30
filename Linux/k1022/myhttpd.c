#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/stat.h>

#define MYPATH "/home/rh/k1022"
void* fun(void*arg);
int main()
{
	int sockfd = sock_create();

	struct sockaddr_in caddr;
	while(1)
	{
		int len = sizeof(caddr);
		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c<0)
		{
			continue;
		}
		printf("c=%d,ip:%s,port:%d\n",c,inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
		pthread_t id;
		pthread_create(&id,NULL,fun,(void*)c);
	}
}
void* fun(void* arg)
{
	int c = (int)arg;
	while(1)
	{
		char buff[1024] = {0};
		int n = recv(c,buff,1023,0);
		if(n <= 0)
		{
			break;
		}

		printf("read(c=%d):\n%s\n",c,buff);
		char* p = NULL;
		char * s = strtok_r(buff," ",&p);
		if(s == NULL)
		{
			break;
		}
		printf("MODE:%s\n",s);

		s = strtok_r(NULL," ",&p);
		if(s == NULL)
		{
			break;
		}
		if(strcmp(s,"/") == 0)
		{
			s = "/index.html";
		}
		char path[256] = {MYPATH};
		strcat(path,s);
		printf("openfile:%s\n",path);

		int fd = open(path,O_RDONLY);
		if(fd == -1)
		{
			break;
		}

		struct stat st;
		stat(path,&st);

		char sendbuff[1024] = {"http/1.1 200 OK\r\n"};
		strcat(sendbuff,"Server:myhttpd\r\n");
		sprintf(sendbuff+strlen(buff),"Content-Length%d\r\n",st.st_size);

		//strcat(sendbuff,"Content-Length: 5\r\n");
		strcat(sendbuff,"\r\n");
		printf("send head:\n%s\n",sendbuff);
		//strcat(buff,"HELLO");
		//printf("send:\n%s\n",sendbuff);
		send(c,sendbuff,strlen(sendbuff),0);
		//send(c,"HELLO",5,0);
		char data[512] = {0};
		int num = 0;
		while((num = read(fd,data,512))>0)
		{
			send(c,data,num,0);
		}
		close(fd);

	}
	close(c);
}
int sock_create()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(80);//http
	saddr.sin_addr.s_addr = inet_addr("192.168.31.63");
	
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);

	listen(sockfd,5);

	return sockfd;
}
