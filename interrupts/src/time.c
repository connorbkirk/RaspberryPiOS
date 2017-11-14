#include "time.h"
#include "mailbox.h"

void wait(uint32_t time){
	uint32_t end = SYSTEMTIMER->timer_lo + time;

	while(SYSTEMTIMER->timer_lo < end){
	}
}

void set_time_irq(uint32_t time){
	SYSTEMTIMER->compare1 = SYSTEMTIMER->timer_lo + time;
}

uint32_t get_time_cycle(){
	return SYSTEMTIMER->timer_lo;
}

/*
 * initialize ARMTIMER but do not enable it.
 * interrupts are disabled
 * 
 * ticks is the number of usecs between overflows/interrupts
 *
 */
void armtimer_init(unsigned ticks){
	ARMTIMER->control.enable_timer = 0;
	ARMTIMER->control.enable_timer_irq = 0;
	ARMTIMER->control.timer_is_32_bit = 1;

	uint32_t buffer[5] = {0,0,0,0,0};
	mailbox_tag_message(buffer, 5, MB_TAG_GET_CLOCK_RATE, 8, 8, 4, buffer[4]);	//get gpu clock
	buffer[4] /= 250;

	ARMTIMER->control.prescale = clckdiv1;	//clock divisor = 1
	ARMTIMER->control.enable_timer = 1;
	ARMTIMER->control.enable_timer_irq = 1;
}
