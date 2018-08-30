#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
int i = 0;
for(;i<2;i++)
{
fork();
printf("A");
}
return 0;
}
