#include "interrupts.h"

void __attribute__((interrupt("UNDEF"))) undef_instr(){
	while(1){
	}
}

void __attribute__((interrupt("SWI"))) swi_handler(){
	while(1){
	}
}

void __attribute__((interrupt("IRQ"))) irq_handler(){
	while(1){
	}
}

void __attribute__((interrupt("FIQ"))) fiq_handler(){
	while(1){
	}
}
