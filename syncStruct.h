#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

struct shared_mem
{
	volatile int first;
	volatile int second;
};

#endif
