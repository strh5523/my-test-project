#include<stdio.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/resource.h>
int main()
{
	int who = RUSAGE_SELF;
	int who1 = RUSAGE_CHILDREN;
	struct rusage usage;
	int ret = getrusage(who,&usage);
	int ret1 = getrusage(who1,&usage);
	if((ret == -1)||(ret1 == -1))
	{
		perror("who error");
		}
	
	fflush(stdout);
	exit(0);
	}
