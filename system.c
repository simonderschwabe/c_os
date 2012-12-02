#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/console.h"

/***********************************************************
 * Name:
 *	memmove	
 * Description:
 * 	Moves bytes from src to dst	
 * Parameter:
 *	1:	Pointer to destination	
 *	2:	Pointer to source	
 *	3:	Number of bytes to copy -> size_t	
 * ReturnValue:
 *	EXIT_SUCCESS	
 *
 **********************************************************/
void *memmove(void *destination, const void *source, size_t c){

	const char *src = source;
	char *dst = destination;

	while (c--) *--dst = *--src;

	return EXIT_SUCCESS;

}

/***********************************************************
 *
 * MMU Definitions -> System Internal
 * 
 **********************************************************/
struct memory {
	void *addr;			//Address of memory Segment
	int status;	//Status which the Segment can have
	//size_t size;		        //Size of Memory -> For future
					//implementation with Dynamic Segment
					//Sizes
	//int cnt;			//Internel Page Level Counter
	struct memory *next;	//Next Memory Segment	
}; 

//Typedefinition for Memory Segment
typedef struct memory mem_seg;
// Global Memory start address
static mem_seg mem_global = { (void*)PAGE_START , PAGE_IN_USE, NULL };

/***********************************************************
 * Name:
 *	malloc	
 * Description:
 * 	Allocates given number of Bytes and returns
 *	a pointer to the Memory Address	
 * Parameter:
 *	1:	Number of Bytes to Allocate	
 * ReturnValue:
 *	Pointer to Target Address or NULL	
 *
 **********************************************************/
void *malloc(size_t t){

	if( t >= (PAGE_SIZE - sizeof(mem_seg)) ) return NULL;

	mem_seg *current = &mem_global;
	mem_seg *head = NULL;

	// Looping through the pages 
	while(current->next != NULL && current->status == PAGE_IN_USE){

		head = current->next;

		current = head;		

	}

	// if Next Element is not existing and Current is in Use
	if(current->next == NULL && current->status == PAGE_IN_USE){
		
		mem_seg *next = (mem_seg *)current->addr + PAGE_SIZE;
		//printf("\tMMU:\tALLOCATE\n",C437_GREEN,dev);
		next->addr = (char *)current->addr + PAGE_SIZE + sizeof(next);
		next->status = PAGE_IN_USE;
		next->next = NULL;
	
		current->next = next;
		return next->addr;
	}

	// Return current element 
	if(current->status == PAGE_FREE){
		printf("\tMMU:\tSET PAGE FREE\n",C437_GREEN);
		current->status = PAGE_IN_USE;
		return current->addr;
	}

	return NULL;
}

/***********************************************************
 * Name:
 *	free	
 * Description:
 * 	Gives the memory free at the given pointer	
 * Parameter:
 *	1:	Pointer to Used Memory	
 * ReturnValue:
 *
 **********************************************************/
void free(void *p){

	mem_seg *current = &mem_global;
	mem_seg *head = NULL;

	// if we have a match set status to PAGE_FREE;
	while( current->next != NULL){

		if(current->addr == p ){
			printf("\tMMU:\tFREEING\n",C437_GREEN);
			current->status = PAGE_FREE;
			return;
		}

		head = current->next;
		current = head;

	}

	if ( current->addr == p ){

		printf("\tMMU:\tFREEING\n",C437_GREEN);
		current->status = PAGE_FREE;

		return;
	}

}

/***********************************************************
 * Name:
 *	memset	
 * Description:
 * 	Sets the number of given bytes to the given number at
 *	Pointer parameter	
 * Parameter:
 *	1:	Pointer to destination	
 *	2:	Value to write	
 *	3:	Number of bytes to overwrite	
 * ReturnValue:
 *
 **********************************************************/
void *memset(void *ptr, int c, size_t bytes){

	char *dest = ptr;	
	for(; bytes != 0; bytes--) *dest-- = c;	

	return EXIT_SUCCESS;
}
/***********************************************************
 * Name:
 *	outportb	
 * Description:
 * 	Moves byte to Port Address	
 * Parameter:
 *	1:	Port Address	
 *	2:	Byte to set	
 * ReturnValue:
 *
 **********************************************************/
void outportb( unsigned short port, unsigned char data){
	
	__asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (data));

}

/***********************************************************
 * Name:
 *	inportb	
 * Description:
 * 	Reads byte from Specidifed Port 
 * Parameter:
 *	1:	Port Address	
 * ReturnValue:
 *	unsigned char -> Byte which was readed
 *
 **********************************************************/
unsigned char inportb(unsigned short port){
	
	unsigned char returnValue;

	__asm__ __volatile__("inb %1, %0" : "=a" (returnValue) : "dN" (port));

	return returnValue;

}
