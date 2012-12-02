#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/system.h"
#include "inc/console.h"

static char *characterBuffer;	//Global Linebuffer
int bufferCount;		//Characters in the Buffer
static char *lastLine;		//Buffer which only contains the Last line

/***********************************************************
 * Name:
 *	initLineBuffer	
 * Description:
 * 	Allocates Memory for the LineBuffer 	
 * Parameter:
 * ReturnValue:
 *	EXIT_SUCCESS	
 *
 **********************************************************/
void initLineBuffer(){

	characterBuffer = malloc(sizeof(char) * CHARACTER_BUFFER_SIZE);
	lastLine = malloc(sizeof(char) * CHARACTER_BUFFER_SIZE);

	bufferCount = 0;

	return;
}

/***********************************************************
 * Name:
 * 	parseCharacter	
 * Description:
 *  	Writes the typed character to the Buffer and prints it in
 * 	the Console. If Enter is pressed, fills the Last line into
 *	lastLine;	
 * Parameter:
 *	1:	Character which should be processed	
 * ReturnValue:
 *
 **********************************************************/
void parseCharacter(char c){

	characterBuffer[bufferCount] = c;
	

	if(c == '\n'){

		int localBufferCount = bufferCount;

		while(localBufferCount-- && localBufferCount >= 0){

			if(characterBuffer[localBufferCount] == '\n') break;	

		}

		for(int i = 0; i < bufferCount - localBufferCount; i++){

			lastLine[i] = characterBuffer[i+localBufferCount];

		}	

		for(int i = bufferCount - localBufferCount; i < CHARACTER_BUFFER_SIZE; i++){

			lastLine[i] = 0;

		}

	}

	if(bufferCount >= CHARACTER_BUFFER_SIZE) bufferCount = 0;
	
	bufferCount++;

	printf(&c,C437_GREEN);

	return;	
}

/***********************************************************
 * Name:
 *	getLastLine	
 * Description:
 * 	Returns a Pointer to the Last Line String	
 * Parameter:
 * ReturnValue:
 *	Pointer to the Last Line	
 *
 **********************************************************/
char *getLastLine(){

	return lastLine;

}
