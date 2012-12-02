#ifndef	DEFINITIONS 
#define	DEFINITIONS 

/***********************************************************
 *
 * Section for Return Codes
 *
 **********************************************************/
#define	EXIT_SUCCESS 	0	//Returncode for SUCCESS	
#define EXIT_FAILURE	1	//Returncode for General Failure
#define EXIT_WARNING	2	//Returncode for Warning

/***********************************************************
 *
 * Section for Systemwide Strings
 *
 **********************************************************/
#define OS_NAME		"c/OS"	//Name of this OS
#define OS_AUTHOR	"Simon Sommer"	//Author
#define OS_ARCH		"i368"	//Architecture String
#define OS_VERSION	"v0.1"	//Version String	

/***********************************************************
 *
 * Section for Systemwide Constants
 *
 **********************************************************/
#define OS_DEVICE_SIZE	64	//Number of Devices 
				//which could be handled
#define PAGE_SIZE	4096	//Default Page size of MMU
#define PAGE_START      0x2096660	//This is where page starts
#define PAGE_IN_USE	0x2	//Page is used
#define PAGE_FREE	0x1	//Page is free

#define INTR_BUF_SIZE	1024	//Buffer Size for keyboard Buffer


/***********************************************************
 *
 * Section for Console Specific Constants
 *
 **********************************************************/
#define CHARACTER_BUFFER_SIZE	2048	//Characters which are typed 
					//an buffered

/***********************************************************
 *
 * Section for Programming Constants
 *
 **********************************************************/
#define NULL	((void *)0)	//NULL Pointer definition

/***********************************************************
 *
 * Video Color Codes, Codepage: IBM 437
 *
 **********************************************************/
#define	C437_BLACK	0x00	//Black 
#define C437_BLUE	0x01	//Blue 
#define C437_GREEN	0x02	//Green
#define C437_CYAN	0x03	//Cyan
#define C437_RED	0x04	//Red
#define C437_MAGENTA	0x05	//Magenta
#define C437_BROWN	0x06	//Brown
#define C437_LIGHTGREY	0x07	//LightGrey
#define C437_LIGHTGREEN	0x10	//LightGreen
#define C437_WHITE	0xF	//White


/***********************************************************
 *
 * Section for Device Type Definitions
 *
 **********************************************************/
#define DEVICE_EMPTY		0x000	//Definition not definied Device
#define	DEVICE_VIDEO		0x001	//Basic Video Output Device
#define DEVICE_KEYBOARD		0x002	//Keyboard Input Device
#define DEVICE_DISK		0x003	//Disk Device
#define DEVICE_NETWORK		0x004	//Network Device
#define DEVICE_SOUND		0x005	//Sound Device

/***********************************************************
 *
 * Interrupt Defintions -> Integer Numbers
 *
 **********************************************************/
#define IRQ_EMPTY	0	//Not defined Interrupt
#define IRQ_32		32	//To be defined
#define IRQ_KEYBOARD	33	//Keyboard Interrupt Number
#define IRQ_34		34	//To be defined
#define IRQ_35		35	//To be defined
#define IRQ_36		36	//To be defined
#define IRQ_37		37	//To be defined
#define IRQ_38		38	//To be defined
#define IRQ_39		39	//To be defined
#define IRQ_40		40	//To be defined
#define IRQ_41		41	//To be defined
#define IRQ_42		42	//To be defined
#define IRQ_43		43	//To be defined
#define IRQ_44		44	//To be defined
#define IRQ_45		45	//To be defined
#define IRQ_46		46	//To be defined
#define IRQ_47		47	//To be defined

#endif
