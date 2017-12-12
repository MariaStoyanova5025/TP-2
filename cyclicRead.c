#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "cyclicBuf.h"
#include "gen.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct buffer* mem = mmap( NULL, sizeof(struct buffer), PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}	
	
	uint64_t i = mem->pos;
	uint64_t check;
	uint64_t lap = 0;
	while(true)
	{
		
		while(i == mem->pos)
		{}
		if(lap < mem->lap  || (lap == mem->lap && mem->pos >= i))
		{
			perror("Write overtakes read");
			break;
		}
		check = verify((void*)mem->buff[i].array);
		if(check == -1)
		{
			perror("Can't verify");
			break;

		}
		if(check != i)
		{
			perror("Seed not correct");
			break;
		}
		i++;
		if(i == 5025)
		{
			i = 0;
			lap++;
		}
	}	

	return 0;
}
