#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "cyclicBuf.h"
#include "gen.h"


int main()
{
	int memFd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXU );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	int res;
	res = ftruncate( memFd, sizeof(struct buffer) );
	if( res == -1 )
	{
		perror("Can't truncate file");
		return res;
	}
	
	struct buffer* mem = mmap( NULL, sizeof(struct buffer), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}
	mem->lap = 0;
	uint32_t i = 0;
	mem->pos = 0;
	while(true)
	{
		generate((void*)mem->buff[mem->pos].array, i);
		i++;
		mem->pos++;
		if(mem->pos == 5025)
		{
			mem->pos = 0;
			i = 0;
			mem->lap++;
		}		
	}	

	return 0;
}
