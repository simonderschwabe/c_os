#ifndef CONSOLE
#define CONSOLE

int printf(char *, int);
void clear_screen();
int setVideoDevice(device*);

/* lineBuffer.c Functions */
void initLineBuffer();
void parseCharacter(char);
char *getLastLine();

#endif
