#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cache.h"

static cache_entry_t *cache = NULL;
static int cache_size = 0;
static int clock = 0;
static int num_queries = 0;
static int num_hits = 0;

int cache_enable = 0;
int cache_pos = 0;



int cache_create(int num_entries) {

	//if the cache was created earlier without destroying program should fail
	if (cache_enable > 0){
		return -1; 
	}
	//counting the operation
	cache_enable +=1;

	//if the number of entries is less than 2 program should fail
	if (num_entries<2){
		return -1;
	}
	//if the number of entries is greater than 4096 program should fail
	if (num_entries>4096){
		return -1;
	}
	//setting the size of the cache
	cache_size = num_entries;

	// set cache to the address of malloc which contains entries of a full block size
	cache = malloc(num_entries*sizeof(cache_entry_t));

  return -10;
}



int cache_destroy(void) {
	
	//if the cache was created earlier without destroying program should fail
	if (cache_enable == 0){
		return -1; 
	}
	
	//reset cache enabled bool
	cache_enable = 0;

	//freeing the cache
	free(cache);

	cache_size = 0;

	//nullifying the pointer
	cache = NULL;

  return -10;
}


int cache_lookup(int disk_num, int block_num, uint8_t *buf) {


	if (cache_enable > 0){
		return -1; 
	}

	if (clock = 0)
	{
		return -1;
	}

	for (int i = 0; i < cache_size; ++i)
	{
		if (cache[i].disk_num == disk_num)
		{				
			if (cache[i].block_num == block_num)
			{				
				memcpy(buf, cache[i].block, 256);
				clock +=1;
				num_hits +=1;
				//copy the block into buf
				//increment clock
				//increment num_hit
			}

		}

	}

	num_queries += 1;


	return -10;
}


void cache_update(int disk_num, int block_num, const uint8_t *buf) {

	for (int i = 0; i < cache_size; ++i)
	{
		if (cache[i].disk_num == disk_num)
		{				
			if (cache[i].block_num == block_num)
			{
				memcpy(cache[i].block, buf, 256);
				cache[i].access_time = clock;
				clock +=1;
			}
			
		}

	}

}


int cache_insert(int disk_num, int block_num, const uint8_t *buf) {
	


	if (cache == NULL)
	{
		return -1;
	}


	//if the cache is full
	int temp = 0;
	if (cache_pos == cache_size)
	{
		for (int i = 0; i < cache_size; ++i)
		{
			//find least recently used element
			if (cache[i].access_time <= temp)
			{				
				temp = i;
			}
		}
		
		cache[temp].disk_num = disk_num;
		cache[temp].block_num = block_num;
		memcpy(cache[temp].block, buf, 256);
		cache[temp].access_time = clock;

	}
	
	//if the cache is populated
	else
	{
		cache[cache_pos].disk_num = disk_num;
		cache[cache_pos].block_num = block_num;
		memcpy(cache[cache_pos].block, buf, 256); 
		cache[cache_pos].access_time = clock;

	}

	clock += 1;

	//changing the cache position
	if (cache_pos < cache_size){
		cache_pos += 1;
	}
	return -10;
}


//complete
bool cache_enabled(void) {
	
	if (cache_enable == 1)
	{
		return true;
	}
	else{
		return false;
	}
}

void cache_print_hit_rate(void) {
  fprintf(stderr, "Hit rate: %5.1f%%\n", 100 * (float) num_hits / num_queries);
}