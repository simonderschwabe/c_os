#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/console.h"
#include "inc/system.h"

/* Default Keymap */
unsigned char kbdde[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '\\', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'z', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'y', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '-',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/* Keyboard SHIFT is pressed */
unsigned char kbdde_upper[128] =
{
    0,  27, '!', '"', 0, '$', '%', '&', '/', '(',	/* 9 */
  ')', '=', '_', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Z', 'U', 'I', 'O', 'P', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'Y', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', ';', ':', '_',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/* Shift Pressed Flag */
unsigned int S_FLAG = 0;
/***********************************************************
 * Name:
 *	irq_keyboard_handler
 * Description:
 * 	Handles Keyboard interrupts and calls lineBuffer function
 *      for further processing of typed key	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void irq_keyboard_handler(){

	unsigned char typedKey;

	typedKey = inportb(0x60);

	if(typedKey & 0x80){

		/* Shift Released */
		if((typedKey == 0x80 + 0x2A) || 
	           (typedKey == 0x80 + 0x36)){

			S_FLAG = 0;

		}

	}
	/* Shift Key Pressed */
	else if((typedKey == 0x2A || typedKey == 0x36) && !((typedKey == 0x1D) || (typedKey == 0x80 + 0x1D))){

		S_FLAG = 1;

	}
	else{

		if(S_FLAG){
			
			parseCharacter(kbdde_upper[typedKey]);
	
		}
		else{

			parseCharacter(kbdde[typedKey]);

		}

	}

	return;
}
