#include "memory.h"

#define LAST_ADDRESS 0x30000000

extern uint32_t kernel_end;

typedef enum{
	FREE,
	RESERVED,
	LOCKED
} BLOCK_STATE;

struct memory_block{
	struct memory_block *next;
	size_t size;
	BLOCK_STATE state;
};

void *heap_start;
void *heap_end;
void *stack_start;
void *stack_end;

struct memory_block *first_block;

void init_memory(){
	heap_start = (void*)LAST_ADDRESS;
	heap_end = (void*)(LAST_ADDRESS - sizeof(struct memory_block));
	
	stack_start = 0;
	stack_end = &kernel_end;

	first_block = (struct memory_block*)((char *)(LAST_ADDRESS - sizeof(struct memory_block)
		- sizeof(uint32_t)));
	first_block->next = NULL;
	first_block->state = LOCKED;
}

void *kmalloc(size_t size){
	return NULL;
}

void *krealloc(void *ptr, size_t size){
	return NULL;
}

void *kcalloc(size_t size){
	return NULL;
}

void kfree(void *ptr){
	struct memory_block *block = (struct memory_block *)((char *)ptr - sizeof(struct memory_block));
	block->state = FREE;
}
