.global _start

_start:
_reset_:
	ldr	r0,	=_isr_vector
	mov	r1,	#0x0000
	ldmia	r0!,	{r2,r3,r4,r5,r6,r7,r8,r9} //load vector items into r2-r9
	stmia	r1!,	{r2,r3,r4,r5,r6,r7,r8,r9} //store r2-r9 into 0x0000
	ldmia	r0!,	{r2,r3,r4,r5,r6,r7,r8,r9}
	stmia	r1!,	{r2,r3,r4,r5,r6,r7,r8,r9}

	mov	sp,	#0x8000
	b	main

_isr_vector:
        ldr     pc,     _reset_h
        ldr     pc,     _undef_instr_h
        ldr     pc,     _sw_interrupt_h
        ldr     pc,     _prefetch_abort_h
        ldr     pc,     _data_abort_h
        ldr     pc,     _unused_h
        ldr     pc,     _interrupt_h
        ldr     pc,     _fast_interrupt_h

_reset_h:               .word   _reset_
_undef_instr_h:         .word   undef_instr
_sw_interrupt_h:        .word   swi_handler
_prefetch_abort_h:      .word   _reset_
_data_abort_h:          .word   _reset_
_unused_h:              .word   _reset_
_interrupt_h:           .word  	irq_handler
_fast_interrupt_h:      .word  	fiq_handler 

hang:
	b	hang

.globl enable_interrupts
enable_interrupts:
	cpsie	i
	bx	lr

.globl	disable_interrupts
disable_interrupts:
	cpsid	i
	bx	lr
