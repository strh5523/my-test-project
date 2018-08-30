#include<stdio.h>
#include<stdlib.h>
#include<poll.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAX 10
void fds_init(struct pollfd fds[])
{
	int i = 0;
	for(;i<MAX;i++)
	{
		fds[i].fd = -1;
		fds[i].events = 0;
		fds[i].revents = 0;
	}

}
void fds_add(struct pollfd fds[],int fd)
{
	int i = 0;
	for(;i<MAX;i++)
	{
		if(fds[i].fd == -1)
		{
			fds[i].fd = fd;
			fds[i].events = POLLIN;
			break;
		}
	}
}
void fds_del(struct pollfd fds[],int fd)
{
	int i = 0;
	for(;i<MAX;i++)
	{
		if(fds[i].fd == fd)
		{
			fds[i].fd = -1;
			fds[i].events = 0;
			break;
		}
	}
}
int create_sock();
int main()
{
	int sockfd = create_sock();
	struct pollfd fds[MAX];
	fds_init(fds);
	
	fds_add(fds,sockfd);
	
	while(1)
	{
		int n = poll(fds,MAX,5000);
		if(n == -1)
		{
			perror("poll error");
		}
		else if(n == 0)
		{
			printf("time out\n");

		}
		else
		{
			int i = 0;
			for(;i<MAX;i++)
			{
				if(fds[i].fd == -1)
				{
					continue;
				}
				if(fds[i].revents & POLLIN)
				{
					if(fds[i].fd == sockfd)
					{
						struct sockaddr_in caddr;
						int len = sizeof(caddr);
						
						int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
						assert(c != -1);
						printf("accept fd =%d,ip=%s\n",c,inet_ntoa(caddr.sin_addr));
						fds_add(fds,c);
					}
						else
						{
							char buff[128] = {0};
							int c = recv(fds[i].fd,buff,127,0);
							if(c<=0)
							{
								printf("cli close\n");
								close(c);
								fds_del(fds,c);
							}
							else
							{
								printf("%s\n",buff);
								memset(buff,0,sizeof(buff));
								send(fds[i].fd,"ok",2,0);
								//fds[i].events = 0
							}
						}
				}
				}
			}
	}
}
int create_sock()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("192.168.31.63");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	
	assert(res != -1);

	listen(sockfd,5);
	return sockfd;
}
