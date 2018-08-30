#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<signal.h>
void fun(int sig)
{
printf("sig=%d\n",sig);
signal(SIGINT,SIG_DFL);
}
int main(int argv,char* argc[],char* envp)
{
//signal(SIGINT,fun);
signal(SIGINT,fun);

while(1)
{
sleep(1);
printf("hello\n");
}
exit(0);
//char* myargc[10] = {"test","-f"};
//char* myenvp[] = {"STR=hello"};
//printf("main pid=%d\n",getpid());
//execve("./test",myargc,myenvp);
//execvp("ps",myargc);//在环境变量PATH所记录的位置搜索ps
//execv("/bin/ps",myargc);
//execle("./test","ps","-f",(char*)0,myenvp);
//execlp("ps","ps","-f",(char*)0);//执行在标准目录下的命令
//execl("./test","test","hello","l23",(char*)0);
//execl("/bin/ps","ps","-f",(char*)0);
//perror("execl error");
//exit(0);
}
