global enableA20

enableA20:
	mov al, 2
	out 0x92, al

	ret
