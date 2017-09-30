#include "hw.h"
#include "types.h"

struct __attribute__((__packed__, aligned(4))) IrqControlRegisters{
	const uint32_t IRQ_pending_basic;
	uint32_t IRQ_pending_1;
	uint32_t IRQ_pending_2;
	uint32_t FIQ_control;
	uint32_t IRQ_enable_1;
	uint32_t IRQ_enable_2;
	uint32_t IRQ_enable_basic;
	uint32_t IRQ_disable_1;
	uint32_t IRQ_disabke_2;
	uint32_t IRQ_disable_basic;
};

#define IRQ ((volatile __attribute__((aligned(4))) struct IrqControlRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0xB200)
