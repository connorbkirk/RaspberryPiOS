#include "hw.h"
#include "types.h"

//Enumerated timer control prescal  --- pg197 of bcm2835.pdf
typedef enum{
	clckdiv1 = 0b00,
	clckdiv2 = 0b01,
	clckdiv3 = 0b10,
	clckdiv_undef = 0b11,
} TIMER_PRESCALE;

//timer control register --- pg197 of bcm2835.pdf
typedef union tagTIMEREGISTER{
	struct{
		unsigned unused: 1;
		unsigned timer_is_32_bit: 1; //0 -> 16 bit, 1 -> 32 bit
		TIMER_PRESCALE prescale : 2;
		unsigned unused1 : 1;
		unsigned enable_timer_irq : 1; //1 = timer interrupts enabled
		unsigned unused2 : 1;
		unsigned enable_timer : 1; // 1 = timer enabled
		unsigned reserved: 24;
	};
	uint32_t raw32;
} time_ctrl_reg_t;

struct __attribute__((__packed__, aligned(4))) SystemTimerRegisters{
	uint32_t control_status;
	uint32_t timer_lo;
	uint32_t time_hi;	
	uint32_t compare0;
	uint32_t compare1;
	uint32_t compare2;
	uint32_t compare3;
};

//arm timer hardware registers --- section 14 bcm2835.pdf
struct __attribute__((__packed__, aligned(4))) ArmTimerRegisters{
	uint32_t load;
	const uint32_t value;
	time_ctrl_reg_t control;
	uint32_t clear;
	const uint32_t rawIRQ;
	const uint32_t maskedIRQ;
	uint32_t reload;
};

#define SYSTEMTIMER ((volatile __attribute((aligned(4))) struct SystemTimerRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0x3000))
#define ARMTIMER ((volatile __attribute((aligned(4))) struct ArmTimerRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0xB400))

void wait(uint32_t time);
void clear_time_irq();
uint32_t get_time_cycle();
void set_time_irq(uint32_t time);
void armtimer_init();
