#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

#include <stdint.h>

struct cyclic_buf
{
	volatile int array[1024];
};

struct buffer
{
	volatile struct cyclic_buf buff[5025];
	volatile uint64_t pos;
	volatile uint64_t lap;

};

#endif
