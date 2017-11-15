#include "interrupts.h"
#include "gfx.h"
#include "act.h"
#include "time.h"

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
	static int lit = 0;

	ARMTIMER->clear = 0;
	
	console_write("INTERRUPTED\n", 12);

	lit = !lit;
	set_act_state(lit);
}

void __attribute__((interrupt("FIQ"))) fiq_handler(){
	while(1){
	}
}
