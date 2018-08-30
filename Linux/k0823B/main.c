#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
int fd = open("./file.txt",O_WRONLY | O_CREAT,0600);
assert(fd != -1);
pid_t pid = fork();
if(pid == 0)
{
sleep(1);
execl("./test","test",(char*)0);
perror("execl error");
}

exit(0);
}
