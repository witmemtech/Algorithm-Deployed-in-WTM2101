#include "ring_cache.h"
#include "stdlib.h"
#include "string.h"

static void critical_enter()
{
}

static void critical_exit()
{
}

static void * ring_malloc(int size)
{
    extern void *pvPortMalloc( size_t xWantedSize );
    pvPortMalloc(size);
}
static void ring_free(void *data)
{
    extern void vPortFree( void *pv );
    vPortFree(data);
}

int Ring_Cache_Init(Ring_Cache * ring , uint16_t size)
{
	if (ring == 0)	return -1;
	memset(ring, 0x00, sizeof(Ring_Cache));
	ring->current_size = 0x00;
	ring->end = 0x00;
	ring->start = 0x00;
	#if Enable_Stack_Malloc == 0x00
		ring->ring_size = RING_CACHE_SIZE;
	#else
		ring->data = (uint8_t *)ring_malloc(size);
		if (ring->data == NULL)
			return -2;
		ring->ring_size = size;
	#endif
	ring->Critical_Section_Entry = critical_enter;
    ring->Critical_Section_Leave = critical_exit;
	return 0x01;
}
int Ring_Cache_Clear(Ring_Cache * ring)
{
	if (ring == 0)	return -1;
	if(ring->Critical_Section_Entry != NULL)
		(*(ring->Critical_Section_Entry))();
    ring->ring_size = 0x00;
	ring->current_size = 0x00;
	ring->end = ring->start;
#if Enable_Stack_Malloc != 0x00
	ring_free(ring->data);
#endif
	if(ring->Critical_Section_Leave != NULL)
		(*(ring->Critical_Section_Leave))();
	
	return 0x01;
}
int Ring_Cache_Push(Ring_Cache * ring , uint8_t data)
{
	if (ring == 0)	return -1;
	if(ring->current_size >= ring->ring_size)
		return 0x00;
	
	if(ring->Critical_Section_Entry != NULL)
		(*(ring->Critical_Section_Entry))();
	
	ring->data[ring->end++] = data;
	if(ring->end >= ring->ring_size)
		ring->end = 0x00;
	ring->current_size++;
	
	if(ring->Critical_Section_Leave != NULL)
		(*(ring->Critical_Section_Leave))();
	
	return 0x01;
}

int Ring_Cache_Push_String(Ring_Cache *ring, uint8_t *data, uint16_t len)
{
	uint16_t r_index = 0;
	if (ring == 0)	return -1;
	if (ring->current_size + len > ring->ring_size)
		return 0x00;

	if (ring->Critical_Section_Entry != NULL)
		(*(ring->Critical_Section_Entry))();

	for (r_index = 0; r_index < len; r_index++)
	{
		ring->data[ring->end++] = data[r_index];
		if (ring->end >= ring->ring_size)
			ring->end = 0x00;
		ring->current_size++;
	}

	if (ring->Critical_Section_Leave != NULL)
		(*(ring->Critical_Section_Leave))();

	return 0x01;
}

int Ring_Cache_Pop(Ring_Cache * ring , uint8_t * data , uint16_t size)
{
	uint16_t r_index = 0x00;
	
	if (ring == 0)	return -1;
	if(ring->Critical_Section_Entry != NULL)
		(*(ring->Critical_Section_Entry))();
	
	if(size > ring->current_size)
		size = ring->current_size;
	while(r_index < size)
	{
		data[r_index] = ring->data[ring->start];
		ring->start+=0x01;
		if(ring->start>= ring->ring_size)
			ring->start = 0x00;
		r_index++;
	}		
	ring->current_size-=size;
	
	if(ring->Critical_Section_Leave != NULL)
		(*(ring->Critical_Section_Leave))();
	
	return size;
}
