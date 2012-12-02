global gdt_reload
extern gdt_p

gdt_reload:
	lgdt[gdt_p]
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	jmp 0x08:reloadReturn
reloadReturn:
	ret

global idt_reload
extern idt_p

idt_reload:
	lidt[idt_p]
	ret
