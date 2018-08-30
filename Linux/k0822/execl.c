#include<stdio.h>
#include<unistd.h>
int main()
{
int a = 10;
int b = 20;
execl("/bin/ls","ls","/home/rh",NULL);
printf("max=%d",a>b?a:b);
exit(0);
}
