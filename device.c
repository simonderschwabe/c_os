#include "inc/definitions.h"
#include "inc/structures.h"

static device devices[OS_DEVICE_SIZE];	//Global Device Array

/***********************************************************
 * Name:
 *	device_setup	
 * Description:
 * 	Intializes an Empty Global Device Array of 
 *      type DEVICE_EMPTY	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void device_setup(){
	
	int i;
	for( i = 0; i < OS_DEVICE_SIZE; i++){

		devices[i].identifier  = i;
		devices[i].baseAddress = NULL;
		devices[i].type	       = DEVICE_EMPTY;
		devices[i].handler     = NULL;
		devices[i].IRQ	       = IRQ_EMPTY;

	}

}

/***********************************************************
 * Name:
 *	initializeDevice	
 * Description:
 * 	Function to initialize a new Device	
 * Parameter:
 *	1:	Unique Identifier of the Device	
 *	2:	Memory Base Pointer of the Device	
 *	3:	Type of device from definitions.h	
 *	4:	Interrupt Handler function -> NULL	
 *	5:	Interrupt Number -> IRQ_EMPTY	
 * ReturnValue:
 *	new Initialize Device	
 *
 **********************************************************/
device initializeDevice(int identifier, char *baseAddress, int type, void *handler, int IRQ){

	int i;
	for( i = 0; i < OS_DEVICE_SIZE; i++ ){
		if(devices[i].type == DEVICE_EMPTY){
			devices[i].identifier = identifier;
			devices[i].baseAddress = baseAddress;
			devices[i].type	= type;	
			devices[i].handler = handler;
			devices[i].IRQ = IRQ;
			break;
		}
	}

	return devices[i];

}

/***********************************************************
 * Name:
 *      getDevice        
 * Description:
 *      Function which searches throud the list for a Device     
 * Parameter:
 *      1:      Unique Identifier of the Device 
 *      2:      Type of device from definitions.h 
 * ReturnValue:
 *      found Device or Pointer to Device NULL 
 *
 **********************************************************/
device *getDevice(int identifier,int type){
	
	int i;
	for( i = 0; i < OS_DEVICE_SIZE; i++){
		if( devices[i].identifier == identifier	&&
		    devices[i].type	  == type ) return &devices[i];
	}

	return NULL;
}

/***********************************************************
 * Name:
 *      getDeviceByIRQ        
 * Description:
 *      Function which searches throud the list for a Device 
 *	which has the given IRQ Number    
 * Parameter:
 *      1:      IRQ Number 
 * ReturnValue:
 *      found Device or Pointer to Device NULL 
 *
 **********************************************************/
device *getDeviceByIRQ(int IRQ){

	int i;
	for( i = 0; i < OS_DEVICE_SIZE; i++){
		if( devices[i].IRQ == IRQ && 
		    devices[i].handler != NULL ) return &devices[i];
	}

	return NULL;	
}
