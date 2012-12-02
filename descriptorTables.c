#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/system.h"

// Single GDT Entry
struct gdt_element{
	unsigned short l_low;		//Seg Size	Bit: 0-15
	unsigned short l_base;		//Seg Base Addr	Bit: 0-15 	
	unsigned char m_base;		//Seg Base Addr	Bit: 16-23 
	unsigned char security;		//Descriptor Privileg Level
	unsigned char type;		//Seg Type
	unsigned char h_base;		//Seg Base Addr Bit: 24-31
}__attribute__((packed));

// Basic Pointer with Max Bytes
struct gdt_pointer{
	unsigned short limit;		//Limit -> GDT Size
	unsigned int base;		//Pointer to the first Entry of GDT
}__attribute__((packed));

// Single IDT Entry
struct idt_element{
	unsigned short l_base;		//Offset	Bit: 0-15
	unsigned short sel;		//Code Segment Selector
	unsigned char a0;		//Always 0
	unsigned char flags;		//Attributes
	unsigned short h_base;		//Offset 	Bit: 16-31
}__attribute__((packed));


//Basic Pointer with Max Bytes
struct idt_pointer{
	unsigned short limit;		//Limit -> IDT Size
	unsigned int base;		//Pointer to the first Entry of IDT
}__attribute__((packed));	

struct gdt_element gdt[3];		//GDT Table Elements
struct gdt_pointer gdt_p;		//GDT Pointer Struct

static struct idt_element idt[256];	//IDT Table Elements. 
					//It is Static that it could be changed later
struct idt_pointer idt_p;		//IDT Pointer Struct

extern void gdt_reload();		//Externel Function to Load GDT
extern void idt_reload();		//External Function to Load IDT
/***********************************************************
 * Name:
 *	gdt_segment	
 * Description:
 * 	Setup an GDT Gate Entry	
 * Parameter:
 *	1:	Number of Entry in the GDT Array	
 *	2:	Base Address	
 *	3:	LIMIT -> Max Memory Address	
 *	4:	Segment Security Flag	
 *	5:	Segment Type	
 * ReturnValue:
 *
 **********************************************************/
void gdt_segment(int number, unsigned long baseAddress, unsigned long limit, unsigned char segSecurity, unsigned char SegType){

	gdt[number].l_base = (baseAddress & 0xFFFF);
	gdt[number].m_base = (baseAddress >> 16) & 0xFF;
	gdt[number].h_base = (baseAddress >> 24) & 0xFF;

	gdt[number].l_low  = (limit & 0xFFFF);
	gdt[number].type   =((limit >> 16) & 0x0F);

	gdt[number].type   |= (SegType & 0xF0);
	gdt[number].security = segSecurity;

}


/***********************************************************
 * Name:
 *	gdt_setup	
 * Description:
 * 	Setup the Global Descriptor Table	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void gdt_setup(){

	gdt_p.limit = sizeof(gdt) -1;
	gdt_p.base  = (unsigned int)&gdt;

	gdt_segment(0,0,0,0,0);
	gdt_segment(1,0,0xFFFFFFFF,0x9A,0xCF);
	gdt_segment(2,0,0xFFFFFFFF,0x92,0xCF);

	gdt_reload();

	return;
}

/***********************************************************
 * Name:
 *	idt_segment	
 * Description:
 * 	Creates one Entry in the IDT	
 * Parameter:
 *	1:	Position in the Array < 256	
 *	2:	Pointer to baseAddress	
 *	3:	Selectors	
 *	4:	flags	
 * ReturnValue:
 *
 **********************************************************/
void idt_segment(int number, unsigned long baseAddress, unsigned short select, unsigned short flags){

	idt[number].l_base = (baseAddress & 0xFFFF);
	idt[number].h_base = (baseAddress >> 16) & 0xFFFF;

	idt[number].sel	   = select;
	idt[number].flags  = flags;
	idt[number].a0 	   = 0;

}
	
/***********************************************************
 * Name:
 *	idt_setup	
 * Description:
 * 	Creates an empty Interrupt Descriptor Table and
 * 	loads it with lidt.	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void idt_setup(){

	idt_p.limit	= sizeof(idt) -1;
	idt_p.base      = (unsigned int)&idt;

	memset(&idt, 0, sizeof(struct idt_element)*256);

	idt_reload();
}
