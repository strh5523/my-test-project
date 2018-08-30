#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<assert.h>
int main()
{
close(1);
int fd = open("file",O_WRONLY);
printf("fd=%d\n",fd);
printf("main over\n");
//close(fd);
exit(0);
}
