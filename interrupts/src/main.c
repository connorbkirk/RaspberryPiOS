#include "types.h"
#include "act.h"
#include "gfx.h"
#include "time.h"
#include "interrupts.h"

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

int main(void){
	int i;

	//initialize bss to 0
        volatile uint32_t* current_address = &__bss_start__;
        uint32_t* end = &__bss_end__;
        while(current_address < end){
                *current_address = 0;
                current_address++;
        }

	console_init();

	for(i = 0; i < 5; i++){	
		set_act_state(1);
		wait(0xf000);
		set_act_state(0);
		wait(0xf000);
	}

	console_write("Turning on interrupts\n", 22);
	wait(0xffff);
	enable_timer_irq();
	armtimer_init();
	enable_interrupts();
	console_write("DONE\n", 5);
	
	while(1);

}
