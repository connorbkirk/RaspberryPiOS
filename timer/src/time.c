#include "time.h"

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


