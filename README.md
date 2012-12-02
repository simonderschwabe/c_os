# Description

c/OS is an x86 Protected Mode Operation System.
Its focus is to provide clean code and structures.
It was originally Build for learning Purpose.
Hopefully in future it will become more than that.

# License

	GPLv2

# Supported Architectures

Currently supported i686

# Requirements

Required Software:

	Netwide Assembler	
	Gnu GCC / Clang	
	Gnu ld
	Gnu make
	Dd
	Grub
	Grub staging images
	MkDosFS

# Build

Generate Kernel Binary:
	
	make

Generate Floppy Image:

	make floppy

# Run

Run with QEMU

	make qemu

# Off Topic

Thanks to all people who did great tutorials on the topic of Basic Kernel
Development
