#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include "syncStruct.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 1 );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct shared_mem* mem = mmap( NULL, 4096, PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	while( true )
	{
		if( mem->second != mem->first )
			return 0;
	}

	return 0;
}
