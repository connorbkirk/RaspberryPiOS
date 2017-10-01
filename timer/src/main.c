#include "types.h"
#include "act.h"
#include "gfx.h"
#include "time.h"

extern void enable_interrupts();

int main(void){
	int i;

	console_init();

	for(i = 0; i < 5; i++){	
		set_act_state(1);
		wait(0xf000);
		set_act_state(0);
		wait(0xf000);
	}

	console_write("Turning on interrupts", 21);
	wait(0xf000);
	enable_interrupts();
	console_write("DONE", 4);

	while(1);

}
