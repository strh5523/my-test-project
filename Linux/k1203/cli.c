#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd != -1 );

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    assert( res != -1 );

    while( 1 )
    {
        char buff[128] = {0};
        fgets(buff,128,stdin);

        buff[strlen(buff)-1] = 0;
		if(strncmp(buff,"end",3) == 0)
		{
			exit(0);
		}
		else
        {
            send(sockfd,buff,strlen(buff),0);
            char buff[512] = {0};
			recv(sockfd,buff,2,0);
            printf("%s\n",buff);
        }
    }
    close(sockfd);
}
