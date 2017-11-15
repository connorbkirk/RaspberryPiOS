.section .init
.global _start

_start:
_reset_:
	ldr	r0,	=_ivt
	mov	r1,	#0x0000
	ldmia	r0!,	{r2,r3,r4,r5,r6,r7,r8,r9} //load vector items into r2-r9
	stmia	r1!,	{r2,r3,r4,r5,r6,r7,r8,r9} //store r2-r9 into 0x0000
	ldmia	r0!,	{r2,r3,r4,r5,r6,r7,r8,r9}
	stmia	r1!,	{r2,r3,r4,r5,r6,r7,r8,r9}

	bl	CheckAndExitHypToSvc

	//setup stack pointers
	msr 	cpsr_c,	#0xD1
	ldr	sp, 	=__fiq_stack
	msr	cpsr_c,	#0xD2
	ldr	sp,	=__irq_stack
	msr	cpsr_c,	#0xD3
	ldr	sp,	=__svc_stack
	
	b	main

_ivt:
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

.section .text.CheckAndExitHypToSvc, "ax", %progbits
.balign	4
.type CheckAndExitHypToSvc, %function
.syntax unified
.arm
CheckAndExitHypToSvc:
	mrs	r0,	cpsr
	and	r1,	r0,	#0x1F
	cmp	r1,	#0x1A
	beq	.HypMode
	mov	r0,	#0
	bx	lr
.HypMode:
	bic	r0,	r0,	#0xF
	orr	r0,	r0,	#0xD3
	mov	r1,	#0
	mcrr	p15,	#4,	r1,	r1,	cr14
	orr	r0,	r0,	#0x100
	msr	spsr_cxsf,	r0
	mov	r0,	#1
	
	.long	0xE12EF30E
	.long	0xE160006E

.size	CheckAndExitHypToSvc, .-CheckAndExitHypToSvc
