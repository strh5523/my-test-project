#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event.h>

int create_socket();
void accept_cb(int fd, short ev, void * arg);
void io_cb(int fd, short ev, void * arg);
int main()
{
    int sockfd = create_socket();

    struct event_base * base = event_init();
    assert( base != NULL );

    struct event* ev_sock = event_new(base,sockfd,EV_READ|EV_PERSIST,accept_cb,(void*)base);
    assert( ev_sock != NULL );
    event_add(ev_sock,NULL);

    event_base_dispatch(base);
    event_free(ev_sock);
    event_base_free(base);

}
void io_cb(int fd, short ev, void * arg)
{
    if ( ev & EV_READ )
    {
        char buff[128] = {0};
        if ( recv(fd,buff,127,0) <= 0 )
        {
            //有问题
            printf("client close\n");
            return ;
        }

        printf("read(fd=%d)=%s\n",fd,buff);
        send(fd,"ok",2,0);

    }
}
void accept_cb(int fd, short ev, void * arg)
{
    if ( ev & EV_READ )
    {
        struct sockaddr_in caddr;
        int len = sizeof(caddr);
        int c = accept(fd,(struct sockaddr*)&caddr,&len);
        if ( c <= 0 )
        {
            return ;
        }

        struct event_base * base = (struct event_base *)arg;
        printf("accept c=%d\n",c);

        struct event * ev_io = event_new(base,c,EV_READ|EV_PERSIST,io_cb,NULL);
        event_add(ev_io,NULL);
    }
}
int create_socket()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    assert( sockfd != -1 );

    struct sockaddr_in saddr;//ipv4
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    assert( res != -1 );

    listen(sockfd,5);

    return sockfd;
}
