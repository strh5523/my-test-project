#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<signal.h>
void fun(int sig)
{
printf("sig=%d\n",sig);
wait(NULL);
}
int main(int argc, char* argv[])
{
int n = 0;
char* s = NULL;
signal(SIGCHLD,SIG_IGN);//仅仅在linux可以，unix不可以
pid_t pid = fork();
assert(pid != -1);
if(pid == 0)
{
n = 3;
s = "child";
}
else
{
n = 5;
s = "parent";
}
int i = 0;
for( ; i<n;i++)
{
sleep(1);
printf("%s\n",s);
}
exit(0);
}
