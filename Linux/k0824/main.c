#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<signal.h>
int main(int argc,char* argv[])
{
if(argc != 3)
{
exit(0);
}
int pid = 0;
int sig = 0;
sscanf(argv[1],"%d",&pid);
sscanf(argv[2],"%d",&sig);

if( kill(pid,sig) == -1)
{
perror("kill error");
}
exit(0);
}
