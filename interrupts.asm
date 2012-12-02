global irq32
global irq33
global irq34
global irq35
global irq36
global irq37
global irq38
global irq39
global irq40
global irq41
global irq42
global irq43
global irq44
global irq45
global irq46
global irq47

extern irq_handler

irq32:
	cli
	mov [interrupt_buffer], dword 32
	jmp irq_register_save
irq33:
	cli
	mov [interrupt_buffer], dword 33
	jmp irq_register_save
irq34:
	cli
	mov [interrupt_buffer], dword 34
	jmp irq_register_save
irq35:
	cli
	mov [interrupt_buffer], dword 35
	jmp irq_register_save
irq36:
	cli
	mov [interrupt_buffer], dword 36
	jmp irq_register_save
irq37:
	cli
	mov [interrupt_buffer], dword 37
	jmp irq_register_save
irq38:
	cli
	mov [interrupt_buffer], dword 38
	jmp irq_register_save
irq39:
	cli
	mov [interrupt_buffer], dword 39
	jmp irq_register_save
irq40:
	cli
	mov [interrupt_buffer], dword 40 
	jmp irq_register_save
irq41:
	cli
	mov [interrupt_buffer], dword 41
	jmp irq_register_save
irq42:
	cli
	mov [interrupt_buffer], dword 42
	jmp irq_register_save
irq43:
	cli
	mov [interrupt_buffer], dword 43
	jmp irq_register_save
irq44:
	cli
	mov [interrupt_buffer], dword 44
	jmp irq_register_save
irq45:
	cli
	mov [interrupt_buffer], dword 45
	jmp irq_register_save
irq46:
	cli
	mov [interrupt_buffer], dword 46
	jmp irq_register_save
irq47:
	cli
	mov [interrupt_buffer], dword 47
	jmp irq_register_save

irq_register_save:
	pusha
	push ds
	push es
	push fs
	push gs
	
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp

	push eax
	push dword [interrupt_buffer]
	call irq_handler 
	pop dword [interrupt_buffer]
	pop eax

	;Restore Stack Pointer to before Interrupt
	mov esp, eax

	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

SECTION .data
	interrupt_buffer dd 0
	
