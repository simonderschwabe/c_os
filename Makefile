### Build Tools and Options
AS 	:= nasm
AS_BIN 	:= bin
AS_ELF	:= elf32
AS_AOUT := aout

CC	:= gcc
CC_OPT	:= -ffreestanding -c -Os -m32 -nostdinc -Werror -Wall -Wextra -std=c99 -O0
CC_DBG  := -g

LD	:= ld
LD_LST	:= scripts/linker.lst
LD_OPT  := -s -m elf_i386 -static
LD_OBJ 	:= *.o
LD_DBF	:= --print-map

### Other Tools
VM    	:= qemu
VM_OPT	:= -no-fd-bootchk -m 1G -boot a -fda 

DD	:= dd
GRUB 	:= grub
CAT	:= cat
SUDO	:= sudo
DOSFS	:= mkdosfs
CP	:= cp
MOUNT	:= mount
UMOUNT	:= umount
MKDIR	:= mkdir
ECHO	:= echo
ISO	:= genisoimage

### Variables
KERNEL_LINK 	:= _kernel.bin
KERNEL_FILE 	:= kernel.bin
FLOPPY_FILE 	:= floppy.img
FLOPPY_SIZE_K 	:= 1440
ISO_FILE	:= cdrom.iso
MOUNT_TARGET 	:= /mnt
MOUNT_OPT	:= -oloop
GRUB_MENU_LST	:= $(GRUB)/menu.lst
GRUB_STAGE_FILE := /usr/lib/grub/i386-pc/stage*
GRUB_FLOPPY_INIT:= scripts/grub_floppy_init.sh

### Default Task
default:
	$(AS) -f $(AS_ELF) -o kernel.o	bootloader.asm
	$(AS) -f $(AS_ELF) -o a20.o	a20.asm
	$(AS) -f $(AS_ELF) -o descriptorTablesAsm.o	descriptorTables.asm
	$(AS) -f $(AS_ELF) -o interruptsAsm.o	interrupts.asm
	$(CC) $(CC_OPT) -o ckernel.o main.c
	$(CC) $(CC_OPT) -o console.o console.c
	$(CC) $(CC_OPT) -o device.o device.c
	$(CC) $(CC_OPT) -o system.o system.c
	$(CC) $(CC_OPT) -o descriptorTables.o descriptorTables.c
	$(CC) $(CC_OPT) -o interrupts.o interrupts.c
	$(CC) $(CC_OPT) -o keyboard.o keyboard.c
	$(CC) $(CC_OPT) -o lineBuffer.o lineBuffer.c

	$(LD) -T $(LD_LST) $(LD_OPT) -o $(KERNEL_FILE) $(LD_OBJ)	

clean:
	rm *.o
	rm *.bin
	rm *.img
	rm *.iso

floppy:

	$(DD) of=$(FLOPPY_FILE) bs=1024 seek=$(FLOPPY_SIZE_K) count=0
	$(SUDO) $(DOSFS) $(FLOPPY_FILE) 

	$(SUDO) $(MOUNT) $(MOUNT_OPT) $(FLOPPY_FILE) $(MOUNT_TARGET)
	$(SUDO) $(MKDIR) $(MOUNT_TARGET)/$(GRUB)
	$(SUDO) $(CP) $(GRUB_STAGE_FILE) $(MOUNT_TARGET)/$(GRUB)
	$(SUDO) $(CP) $(GRUB_MENU_LST) $(MOUNT_TARGET)/$(GRUB)
	$(SUDO) $(CP) $(KERNEL_FILE) $(MOUNT_TARGET)/$(GRUB)
	$(SUDO) $(UMOUNT) $(MOUNT_TARGET) 

	$(GRUB_FLOPPY_INIT)
	
qemu:
	$(VM) $(VM_OPT) $(FLOPPY_FILE)

iso:
	$(ISO) -pad -b $(FLOPPY_FILE) -R -o $(ISO_FILE) $(FLOPPY_FILE)
