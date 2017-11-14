#include "hw.h"
#include "types.h"

extern void enable_interrupts();

void enable_timer_irq();

typedef union tagENABLEBASICIRQREGISTER{
	union{
		struct{
			unsigned Enable_Timer_IRQ : 1;
			unsigned Enable_Mailbox_IRQ : 1;
			unsigned Enable_Doorbell0_IRQ : 1;
			unsigned Enable_Doorbell1_IRQ : 1;
			unsigned Enable_GPU0_halted_IRQ : 1;
			unsigned Enable_GPU1_halted_IRQ : 1;
			unsigned Enable_Illegal_access_type1 : 1;
			unsigned Enable_Illegal_access_type0 : 1;
			unsigned reserved : 24;
		};
		uint32_t raw32;
	};
} irq_enable_basic_reg_t;

struct __attribute__((__packed__, aligned(4))) IrqControlRegisters{
	const uint32_t IRQ_pending_basic;
	uint32_t IRQ_pending_1;
	uint32_t IRQ_pending_2;
	uint32_t FIQ_control;
	uint32_t IRQ_enable_1;
	uint32_t IRQ_enable_2;
	irq_enable_basic_reg_t IRQ_enable_basic;
	uint32_t IRQ_disable_1;
	uint32_t IRQ_disable_2;
	uint32_t IRQ_disable_basic;
};

#define IRQ ((volatile __attribute__((aligned(4))) struct IrqControlRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0xB200))

