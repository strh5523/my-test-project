#include<stdio.h>
#include<fcntl.h>
#include<assert.h>
int main()
{
int fd = open("passwd",O_RDONLY);
int fw = open("./newpasswd",O_WRONLY | O_CREAT,0600);
assert(fd != -1);

char buff[128] = {0};
int tmp = read(fd,buff,127);
for(;tmp != 0;tmp = read(fd,buff,127))
{
write(fw,buff,tmp);
}
close(fd);
close(fw);
return 0;
}
