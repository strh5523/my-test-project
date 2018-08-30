#include<stdio.h>
#include<unistd.h>
int main()
{
char* envp = {NULL};
execle("./main","main",NULL,envp);
exit(0);
}
