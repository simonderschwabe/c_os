#ifndef	STRUCTURES 
#define	STRUCTURES 

/***********************************************************
 *
 * Kernel Memory Management Structure 
 *
 **********************************************************/

/***********************************************************
 *
 * Kernel Device Management Structure 
 *
 **********************************************************/
//Represents a Device
typedef struct {

	int identifier;		//Unique Device ID
	char *baseAddress;	//Pointer to the Base Address
	int type;		//Out of definitions.h
	void *handler;		//Interrupt Handler. 
				//NULL if no Interruptable Device
	int IRQ;		//Interrupt Number -> defintions.h

} device;

/**********************************************************
 *
 * Types
 *
 *********************************************************/
typedef unsigned int 	size_t;	//size_t definition
typedef unsigned int 	u32int;	//unsigned int 32
typedef 	 int 	s32int;	//signed int 32
typedef	unsigned short 	u16int; //unsigned short 
typedef 	 short	s16int;	//signed shor
typedef	unsigned char	u8int;	//unsigned char
typedef		 char	s8int;	//signed char

#endif
