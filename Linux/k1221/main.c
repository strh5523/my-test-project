#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<stdint.h>
#include<fcntl.h>

int max()
{

}
uint64_t vaddr_to_phy(unsigned vaddr)
{
	int page_size = getpagesize();
	int index = vaddr / page_size;
	int offset = vaddr % page_size;

	int file_offset = index * 8;

	int fd = open("/proc/self/pagemap",O_RDONLY);
	if(fd == -1)
	{
		return 0;
	}
	
	lseek(fd,file_offset,SEEK_SET);

	uint64_t val = 0;

	read(fd,&val,sizeof(uint64_t));
	
	uint64_t phy_index = 0;
	uint64_t phy_addr = 0;
	if(val & ((uint64_t)1 <<63))
	{
		phy_index = val & ((uint64_t)1 << 55) - 1;
		phy_addr = phy_index * page_size + offset;
		return phy_addr;
	}
	else
	{
		printf("not in \n");
		return 0;
	}
}

int main()
{
	int a = 10;
	uint64_t addr = 0;

	addr = vaddr_to_phy((unsigned)&a);
	printf("&a=%x,phy:&a=%x\n",&a,addr);
}
	
