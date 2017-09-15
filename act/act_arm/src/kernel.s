.section .init
.global _start

_start:
	mov	sp,	#0x8000
	b	main

.section .text
main:
	bl	stall
	mov	r0,	#1
	bl	SetACTState

	bl	stall
	mov	r0,	#0
	bl	SetACTState
	
	b	main

stall:
	mov	r0,	#0xf0000
	loop:
		sub	r0,	#1
		cmp	r0,	#0
		bne	loop
	mov	pc,	lr
	
