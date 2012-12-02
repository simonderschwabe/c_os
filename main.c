#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/console.h"
#include "inc/device.h"
#include "inc/system.h"


/***********************************************************
 * Name:
 *	main	
 * Description:
 * 	Start Function of the Kernel	
 * Parameter:
 * ReturnValue:
 *	EXIT_SUCCESS	
 *
 **********************************************************/
void main() {

	/* Global Descriptor Table setup */
	gdt_setup();

	/* Interrupt Descriptor Table setup */
	idt_setup();

	/* Setup Interrupts */
	irq_setup();

	/* Setup Empty Devices */
	device_setup();

	/* Initialize Video Device -> Device does not send Interrupts */
	initializeDevice(0,(char *)0xB8000,DEVICE_VIDEO,NULL,IRQ_EMPTY);

	/* Initialize Keyboard Handler */
	initializeDevice(1,NULL,DEVICE_KEYBOARD,irq_keyboard_handler,IRQ_KEYBOARD);

	/* set Video Device for Console */
	setVideoDevice(getDevice(0,DEVICE_VIDEO));

	/* Initialize the Character Buffer */
	initLineBuffer();

	/* Clear Screen on Video Device */
	clear_screen();

	/* Printing OS Headers */
	printf("\t\t-------------------------\n", C437_GREEN);
	printf("\t\tWELLCOME TO "OS_NAME"\n", C437_GREEN);
	printf("\t\t-------------------------\n", C437_GREEN);

        printf("\t\t"OS_NAME" version "OS_VERSION", Copyright (C) 2012 Simon Sommer\n", C437_CYAN); 
    	printf("\t\t"OS_NAME" comes with ABSOLUTELY NO WARRANTY.\n", C437_CYAN);
    	printf("\t\tThis is free software, and you are\n", C437_CYAN); 
	printf("\t\twelcome to redistribute it under certain conditions.\n", C437_CYAN);

	/* Enable Full 4GB Memory */
	enableA20();
	printf("\t\tA20 GATE ACTIVATED\n", C437_GREEN);

	/* Gives Feedback of previus done Tasks */
	printf("\t\tGDT SETUP DONE\n", C437_GREEN);
	printf("\t\tIDT SETUP DONE\n", C437_GREEN);
	printf("\t\tIRQ SETUP DONE\n", C437_GREEN);

	/* Enable Iterrupts */
	__asm__ __volatile__ ("sti");
	printf("\t\tINTERRUPTS ENABLED\n", C437_GREEN);

	while(1);

	/* TODO: Malloc and Free Debug and Final Test */
}
