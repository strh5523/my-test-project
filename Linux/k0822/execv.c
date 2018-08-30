#include<stdio.h>
#include<unistd.h>
int main()
{
char* argv[] = {"ls","/home/rh",NULL};
execv("/bin/ls",argv);
exit(0);
}
