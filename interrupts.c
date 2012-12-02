#include "inc/definitions.h"
#include "inc/structures.h"
#include "inc/system.h"
#include "inc/console.h"
#include "inc/device.h"

/***********************************************************
 * 
 * Predefined External Interrupts in interrupts.asm 
 *
 **********************************************************/
extern void irq32();
extern void irq33();
extern void irq34();
extern void irq35();
extern void irq36();
extern void irq37();
extern void irq38();
extern void irq39();
extern void irq40();
extern void irq41();
extern void irq42();
extern void irq43();
extern void irq44();
extern void irq45();
extern void irq46();
extern void irq47();

/***********************************************************
 * Name:
 *	irq_remap	
 * Description:
 * 	Remap IRQs to prevent Triplefault	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void irq_remap(){

	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);	
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);

}

/***********************************************************
 * Name:
 *	irq_setup	
 * Description:
 * 	Sets up the interrupts 32-47
 * Parameter:
 * ReturnValue:
 *	EXIT_SUCCESS	
 *
 **********************************************************/
void irq_setup(){
	
	irq_remap();

	idt_segment(IRQ_32, (unsigned)irq32, 0x08, 0x8E);
	idt_segment(IRQ_KEYBOARD, (unsigned)irq33, 0x08, 0x8E);
	idt_segment(IRQ_34, (unsigned)irq34, 0x08, 0x8E);
	idt_segment(IRQ_35, (unsigned)irq35, 0x08, 0x8E);
	idt_segment(IRQ_36, (unsigned)irq36, 0x08, 0x8E);
	idt_segment(IRQ_37, (unsigned)irq37, 0x08, 0x8E);
	idt_segment(IRQ_38, (unsigned)irq38, 0x08, 0x8E);
	idt_segment(IRQ_39, (unsigned)irq39, 0x08, 0x8E);
	idt_segment(IRQ_40, (unsigned)irq40, 0x08, 0x8E);
	idt_segment(IRQ_41, (unsigned)irq41, 0x08, 0x8E);
	idt_segment(IRQ_42, (unsigned)irq42, 0x08, 0x8E);
	idt_segment(IRQ_43, (unsigned)irq43, 0x08, 0x8E);
	idt_segment(IRQ_44, (unsigned)irq44, 0x08, 0x8E);
	idt_segment(IRQ_45, (unsigned)irq46, 0x08, 0x8E);
	idt_segment(IRQ_46, (unsigned)irq46, 0x08, 0x8E);
	idt_segment(IRQ_47, (unsigned)irq47, 0x08, 0x8E);

}

/***********************************************************
 * Name:
 *	irq_handler	
 * Description:
 * 	Global interrupt handler. From here it is decieded
 * 	which custom handler should be started if reqistered	
 * Parameter:
 * ReturnValue:
 *
 **********************************************************/
void irq_handler(int x){

	device *dev = getDeviceByIRQ(x);

	if(dev != NULL){
		void (*handler)(void) = dev->handler;
		handler();		
	}

	outportb(0x20, 0x20);

	return;
}
