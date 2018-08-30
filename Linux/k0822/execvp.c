#include<stdio.h>
#include<unistd.h>
int main()
{
char* argc[] = {"ls","/home/rh","NULL"};
execvp("ls",argc);
exit(0);
}
