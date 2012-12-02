#ifndef SYSTEM
#define SYSTEM

// system.c functions //
void *memmove(void*,const void*,size_t);
void *malloc(size_t);
void free(void*);
void *memset(void*,int,size_t);
void outportb(unsigned short, unsigned char);
unsigned char inportb(unsigned short);
extern void enableA20(void);

// descriptorTabls.c functions //
void gdt_setup(void);
void idt_setup(void);
void idt_segment(int,unsigned long,unsigned short, unsigned short);

// interrupts.c functions //
void irq_setup();

// keyboard.c functions //
void irq_keyboard_handler();

#endif
