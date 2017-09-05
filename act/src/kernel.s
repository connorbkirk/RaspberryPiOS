.section .init
.global _start

_start:
	mov	sp,	#0x8000
	b	main

.section .text
main:
	mov	r0,	#1
	bl	SetACTState

hang:
	b	hang
