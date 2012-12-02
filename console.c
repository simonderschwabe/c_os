#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/console.h"
#include "inc/system.h"

void print_char(char,int,device*);

/***********************************************************
 *
 * Screen Definitions
 * 
 **********************************************************/
static char x = 0;	// X Position of current Screen location 
static char y = 0;	// Y Position of current Screen location
static device *videoDevice;	//VIDEO Device to Print
				//Will be set ones at Boot 

/***********************************************************
 * Name:
 *	printf
 * Description:
 * 	Prints String with Specified Color to Device if
 * 	Device Type equals to DEVICE_VIDEO
 * Parameter:
 *	1:	String which should be printed
 *	2:	Color from definitions.h
 *	3:	device Pointer to which should be printed
 * ReturnValue:
 *	Defaul EXIT_SUCCESS else EXIT_FAILURE
 *
 **********************************************************/
int printf(char *string, int color){

	if(videoDevice->type == DEVICE_VIDEO){

		while(*string){
			print_char(*string,color,videoDevice);
			string++;
		}

	}
	else return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/***********************************************************
 * Name:
 *	move_cursor	
 * Description:
 * 	Moves the cursor to the next character	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void move_cursor(){

	u16int cursorLocation = y * 80 + x;

	outportb(0x3D4, 14);
	outportb(0x3D5, cursorLocation >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, cursorLocation);

}

/***********************************************************
 * Name:
 *	clear_screen	
 * Description:
 * 	clears the whole Screen to black	
 * Parameter:
 *	1:	Pointer to the VIDEO_DEVICE struct	
 * ReturnValue:
 *
 **********************************************************/
void clear_screen(device *device){

	char *videomem = device->baseAddress;

	for(videomem+=4000; videomem != device->baseAddress; videomem--){

		*videomem = 0;

	}
}

/***********************************************************
 * Name:
 *	print_char	
 * Description:
 * 	Prints a signel Char to the Device Specified and
 *	moves cursor acordingly to Linebreaks or Lineends	
 * Parameter:
 *	1:	Character which should be printed	
 *	2:	Character Color -> definitions.h C437_*	
 *	3:	device pointer to type VIDEO_DEVICE	
 * ReturnValue:
 *
 **********************************************************/
void print_char(char c, int color, device *device){

	char *videomem = device->baseAddress;

	//Backspace
	if( c == 0x08 && x){
		x--;
	}	
	// Carriage return resets the X	
	else if ( c == '\r' ){
		x = 0;
	}	
	// Newline
	else if ( c == '\n' ) {
		x = 0;
		y++;
		y++;
	}
	// Tabulator
	else if ( c == 0x09 ){
		x = (x + 8) & ~(8 - 1);
	}
	// Other Characters
	else {
		videomem  =  device->baseAddress + ( y * 80 ) + (x++);
		*videomem = (unsigned char)c ;
		videomem++;
		*videomem = color;
		videomem++;
		x++;	
	}
	// Newline
	if( x >= 120 ){
		x = 0;
		y++;
		y++;
	}
	// New Page -> Cleanup 
	if( y >= 50 ){
		clear_screen(device);
		y = 0;		
	}

	move_cursor();
}

/***********************************************************
 * Name:
 *	setVideoDevice	
 * Description:
 * 	Sets the Current Video Device where the Console printf
 *	should display its characters	
 * Parameter:
 *	1:	Pointer to Video Device of type Device	
 * ReturnValue:
 *	EXIT_SUCCESS	
 *
 **********************************************************/
int setVideoDevice(device *dev){

	videoDevice = dev;

	return EXIT_SUCCESS;
}
