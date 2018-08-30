#include<stdio.h>
#include<wait.h>
#include<assert.h>
#include<unistd.h>
int main()
{
char* s = NULL;
int n = 0;
pid_t pid = fork();
assert(pid != -1);
if(pid == 0)
{
n = 3;
s = "child";
}
else 
{
n = 7;
s = "parent";
int val = 0;
pid_t id = wait(&val);

if(WIFEXITED(val))
{
printf("id=&d,val=%d\n",id,WEXITSTATUS(val));

}

}

int i = 0;
for(;i<n;i++)
{
printf("pid=%d,ppid=%d,s=%s\n",getpid(),getppid(),s);
sleep(1);
}
exit(0);
}
