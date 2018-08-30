#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
int main(int argv,char* argc[],char* envp[])
{
int i = 0;
for( ;i <argv;i++)
{
 
printf("argc[%d]=%s\n",i,argc[i]);
}
for(i=0;envp[i]!=0;i++)
{
printf("envp[%d]=%s\n",i,envp[i]);
}
printf("test pid=%d\n",getpid());
exit(0);
}
