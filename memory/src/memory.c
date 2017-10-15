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

void increment_heap(size_t size){
	//TODO
}

void *kmalloc(size_t size){
	struct memory_block *current = first_block;
	
	bool finished = false;

	do{
		if(current->state == FREE && current->size >= size){
			return (void *)((char *)current + sizeof(struct memory_block));
		}
		
		if(current->next != NULL){
			current = current->next;
		}else if((char *)current - (size + sizeof(struct memory_block)) < (char *)heap_end){
			increment_heap((size + sizeof(struct memory_block)) - ((uint32_t)current - (uint32_t)heap_end));
			
			struct memory_block *new_block = (struct memory_block*) heap_end;
			new_block->next = NULL;
			new_block->size = size;
			new_block->state = LOCKED;

			current->next = new_block;

			return (void *)((char *)new_block + sizeof(struct memory_block));
		}else{
			finished = true;
		}
	}while(!finished);
	return NULL;
}

void *krealloc(void *ptr, size_t size){
	struct memory_block *block = (struct memory_block *)((char*)ptr - sizeof(struct memory_block));

	if(block->size >= size){
		return ptr;
	}
	
	block->state = FREE;
	
	return kmalloc(size);
}

void *kcalloc(size_t size){
	void *ptr = kmalloc(size);
	uint8_t i;
	
	for(i = 0; i < size; i++){
		*((uint8_t *)ptr + i) = 0;
	}

	return ptr;
}

void kfree(void *ptr){
	struct memory_block *block = (struct memory_block *)((char *)ptr - sizeof(struct memory_block));
	block->state = FREE;
}
