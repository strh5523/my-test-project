#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<string.h>

int main()
{
	int fdr = open("./fifo",O_RDONLY);
	assert(fdr != -1);
	printf("fdr =%d\n",fdr);

	//char buff[128] = {0};
	//printf("input:\n");
	//fgets(buff,128,stdin);
	int a;
	while(1)
	{
		char buff[128] = {0};
		//strcpy(buff,buff[strlen(buff)-1]);
		int a = read(fdr,buff,127);
		printf("%s\n",buff);
		if(a == 0)
		{
			break;
			}
	}
	close(fdr);
}
