#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "dumbShmStruct.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXO );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	int res;
	res = ftruncate( memFd, 4096 );
	if( res == -1 )
	{
		perror("Can't truncate file");
		return res;
	}
	
	struct shared_mem* mem = mmap( NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	char* str = "shared_mem_transfer!11!1";
	memcpy( mem->lala, str, strlen(str) + 1 );

	return 0;
}
