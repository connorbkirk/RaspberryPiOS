#include "time.h"
#include "mailbox.h"

void wait(uint32_t time){
	uint32_t end = SYSTEMTIMER->timer_lo + time;

	while(SYSTEMTIMER->timer_lo < end);
}

void set_time_irq(uint32_t time){
	SYSTEMTIMER->compare1 = SYSTEMTIMER->timer_lo + time;
}

uint32_t get_time_cycle(){
	return SYSTEMTIMER->timer_lo;
}

void armtimer_init(){
	ARMTIMER->load = 0x400;

	ARMTIMER->control.timer_is_32_bit = 1;
	ARMTIMER->control.prescale = clckdiv3;
	ARMTIMER->control.enable_timer_irq = 1;
	ARMTIMER->control.enable_timer = 1;
}
