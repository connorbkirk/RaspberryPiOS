#include "types.h"
#include "act.h"
#include "gfx.h"
#include "time.h"
#include "interrupts.h"

int main(void){
	int i;

	console_init();

	for(i = 0; i < 5; i++){	
		set_act_state(1);
		wait(0xf000);
		set_act_state(0);
		wait(0xf000);
	}

	console_write("Turning on interrupts\n", 22);
	wait(0xf000);
	enable_interrupts();
	console_write("DONE\n", 5);
	enable_timer_irq();
	set_time_irq(10000000);
	
	while(1);

}
