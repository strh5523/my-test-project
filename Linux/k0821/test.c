#include<stdio.h>
#include<fcntl.h>
int main()
{
int fd = open("file",O_WRONLY | O_CREAT,0600);
pid_t pid = fork();
if(pid == 0)
{

write(3,"hello",5);
}
close(fd);
}
