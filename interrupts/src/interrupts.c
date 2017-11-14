#include "interrupts.h"
#include "gfx.h"

void enable_timer_irq(){
	IRQ->IRQ_enable_basic.Enable_Timer_IRQ = 1;
}

void __attribute__((interrupt("UNDEF"))) undef_instr(){
	while(1){
	}
}

void __attribute__((interrupt("SWI"))) swi_handler(){
	while(1){
	}
}

void __attribute__((interrupt("IRQ"))) irq_handler(){
	console_write("INTERRUPTED\n", 12);
}

void __attribute__((interrupt("FIQ"))) fiq_handler(){
	while(1){
	}
}
