#include "hw.h"
#include "types.h"

struct __attribute__((__packed__, aligned(4))) SystemTimerRegisters{
	uint32_t control_status;
	uint32_t timer_lo;
	uint32_t time_hi;	
	uint32_t compare0;
	uint32_t compare1;
	uint32_t compare2;
	uint32_t compare3;
};

struct __attribute__((__packed__, aligned(4))) ArmTimerRegisters{
	uint32_t load;
	uint32_t value;
	uint32_t control;
	uint32_t clear;
	uint32_t rawIRQ;
	uint32_t maskedIRQ;
	uint32_t reload;
};

#define SYSTEMTIMER ((volatile __attribute((aligned(4))) struct SystemTimerRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0x3000))
#define ARMTIMER ((volatile __attribute((aligned(4))) struct ArmTimerRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0xB400))

void wait(uint32_t time);
void clear_time_irq();
uint32_t get_time_cycle();

