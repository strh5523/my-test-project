#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include<fcntl.h>

int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));//清空
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert( res != -1);

	printf("connect success\n");
	while( 1 )
	{
		printf("input: ");
		char buff[128] = {0};
		fgets(buff,128,stdin);
		buff[strlen(buff)-1] = 0;
		char send_buff[128] = {0};
		strcpy(send_buff,buff);

		char * myargv[10] = {0};
		char *s = strtok(buff," ");
		if(s == NULL)
		{
			continue;
		}
			myargv[0] = s;
			int i = 1;
			while((s=strtok(NULL," ")))
			{
				myargv[i++] = s;
			}
		if(strcmp(myargv[0],"end") == 0)
		{
			break;
		}

		else if(strcmp(myargv[0],"put") == 0)
		{
			send(sockfd,send_buff,strlen(send_buff),0);
			int fdr = open(myargv[1],O_RDONLY);
			assert(fdr != -1);
			int n = 1;
			int num = 0;
			while(n)
			{
				char buff1[256] = {0};
				n = read(fdr,buff1,256);
				num += n;
			}
			close(fdr);
			int size[1] = {num};
			send(sockfd,size,sizeof(size),0);//get file size

			printf("%s size is %d\n",myargv[1],size[0]);

			int fdr1 = open(myargv[1],O_RDONLY);
			assert(fdr1 != -1);
			int m = 0;
			int num1 = 0;
			while(size[0])
			{
				char buff2[256] = {0};
				m = read(fdr,buff2,256);
				send(sockfd,buff2,m,0);
				num1 += m;
				float rate = num1/size[0];
				printf("%3.2fwait...\n",rate*100);
				size[0] -= m;

			}
			close(fdr1);
			char put_buff[128] = {0};
			recv(sockfd,put_buff,127,0);
			printf("%s\n",put_buff);
			continue;
		}
		else if(strcmp(myargv[0],"get") == 0)
		{
			send(sockfd,send_buff,strlen(send_buff),0);
			int fdw = open(myargv[1],O_WRONLY | O_CREAT,0600);
			assert(fdw != -1);
			int size[1] = {0};
			recv(sockfd,size,256,0);
			printf("%s size is %d\n",myargv[1],size[0]);
			int n = 0;
			int num = 0;
			while(size[0] > 0)
			{
				char buff1[256] = {0};
				recv(sockfd,buff1,256,0);
				n = write(fdw,buff1,strlen(buff1));
				num += n;
				float rate = num/size[0];
				printf("%3.2fwait...\n",rate*100);
				size[0] -= n;
			}
			close(fdw);
			printf("get success\n");
			continue;
		}
		else
		{
			send(sockfd,send_buff,strlen(send_buff),0);	
		
			memset(send_buff,0,strlen(send_buff));
			recv(sockfd,send_buff,127,0);
			if(strcmp(send_buff,"$error$") == 0)
			{
				continue;
			}
			/*if(strcmp(send_buff,"execv: :No such file or directory") == 0)
			{
				printf("bash: %s: command not found\n",buff);
				continue;
			}*/
			printf("%s\n",send_buff);
		}
	}
	close(sockfd);
}
	
	

