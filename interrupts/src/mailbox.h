#ifndef	MAILBOX_H 
#define MAILBOX_H

#include "types.h"
#include "hw.h"

typedef enum {
	/* Videocore info commands */
	MB_TAG_GET_VERSION				= 0x00000001,			// Get firmware revision

	/* Hardware info commands */
	MB_TAG_GET_BOARD_MODEL				= 0x00010001,			// Get board model
	MB_TAG_GET_BOARD_REVISION			= 0x00010002,			// Get board revision
	MB_TAG_GET_BOARD_MAC_ADDRESS			= 0x00010003,			// Get board MAC address
	MB_TAG_GET_BOARD_SERIAL				= 0x00010004,			// Get board serial
	MB_TAG_GET_ARM_MEMORY				= 0x00010005,			// Get ARM memory
	MB_TAG_GET_VC_MEMORY				= 0x00010006,			// Get VC memory
	MB_TAG_GET_CLOCKS				= 0x00010007,			// Get clocks

	/* Power commands */
	MB_TAG_GET_POWER_STATE				= 0x00020001,			// Get power state
	MB_TAG_GET_TIMING				= 0x00020002,			// Get timing
	MB_TAG_SET_POWER_STATE				= 0x00028001,			// Set power state

	/* GPIO commands */
	MB_TAG_GET_GPIO_STATE				= 0x00030041,			// Get GPIO state
	MB_TAG_SET_GPIO_STATE				= 0x00038041,			// Set GPIO state

	/* Clock commands */
	MB_TAG_GET_CLOCK_STATE				= 0x00030001,			// Get clock state
	MB_TAG_GET_CLOCK_RATE				= 0x00030002,			// Get clock rate
	MB_TAG_GET_MAX_CLOCK_RATE			= 0x00030004,			// Get max clock rate
	MB_TAG_GET_MIN_CLOCK_RATE			= 0x00030007,			// Get min clock rate
	MB_TAG_GET_TURBO				= 0x00030009,			// Get turbo

	MB_TAG_SET_CLOCK_STATE				= 0x00038001,			// Set clock state
	MB_TAG_SET_CLOCK_RATE				= 0x00038002,			// Set clock rate
	MB_TAG_SET_TURBO				= 0x00038009,			// Set turbo

	/* Voltage commands */
	MB_TAG_GET_VOLTAGE				= 0x00030003,			// Get voltage
	MB_TAG_GET_MAX_VOLTAGE				= 0x00030005,			// Get max voltage
	MB_TAG_GET_MIN_VOLTAGE				= 0x00030008,			// Get min voltage

	MB_TAG_SET_VOLTAGE				= 0x00038003,			// Set voltage

	/* Temperature commands */
	MB_TAG_GET_TEMPERATURE				= 0x00030006,			// Get temperature
	MB_TAG_GET_MAX_TEMPERATURE			= 0x0003000A,			// Get max temperature

	/*Memory commands */
	MB_TAG_ALLOCATE_MEMORY				= 0x0003000C,			// Allocate Memory
	MB_TAG_LOCK_MEMORY				= 0x0003000D,			// Lock memory
	MB_TAG_UNLOCK_MEMORY				= 0x0003000E,			// Unlock memory
	MB_TAG_RELEASE_MEMORY				= 0x0003000F,			// Release Memory
																	
	/* Execute code commands */
	MB_TAG_EXECUTE_CODE				= 0x00030010,			// Execute code

	/* QPU control commands */
	MB_TAG_EXECUTE_QPU				= 0x00030011,			// Execute code on QPU
	MB_TAG_SET_ENABLE_QPU				= 0x00030012,			// QPU enable

	/*Displaymax commands */
	MB_TAG_GET_DISPMANX_HANDLE			= 0x00030014,			// Get displaymax handle
	MB_TAG_GET_EDID_BLOCK				= 0x00030020,			// Get HDMI EDID block

	/* SD Card commands */
	MB_GET_SDHOST_CLOCK				= 0x00030042,			// Get SD Card EMCC clock
	MB_SET_SDHOST_CLOCK				= 0x00038042,			// Set SD Card EMCC clock

	/* Framebuffer commands */
	MB_TAG_ALLOCATE_FRAMEBUFFER			= 0x00040001,			// Allocate Framebuffer address
	MB_TAG_BLANK_SCREEN				= 0x00040002,			// Blank screen
	MB_TAG_GET_PHYSICAL_WIDTH_HEIGHT		= 0x00040003,			// Get physical screen width/height
	MB_TAG_GET_VIRTUAL_WIDTH_HEIGHT			= 0x00040004,			// Get virtual screen width/height
	MB_TAG_GET_COLOUR_DEPTH				= 0x00040005,			// Get screen colour depth
	MB_TAG_GET_PIXEL_ORDER				= 0x00040006,			// Get screen pixel order
	MB_TAG_GET_ALPHA_MODE				= 0x00040007,			// Get screen alpha mode
	MB_TAG_GET_PITCH				= 0x00040008,			// Get screen line to line pitch
	MB_TAG_GET_VIRTUAL_OFFSET			= 0x00040009,			// Get screen virtual offset
	MB_TAG_GET_OVERSCAN				= 0x0004000A,			// Get screen overscan value
	MB_TAG_GET_PALETTE				= 0x0004000B,			// Get screen palette

	MB_TAG_RELEASE_FRAMEBUFFER			= 0x00048001,			// Release Framebuffer address
	MB_TAG_SET_PHYSICAL_WIDTH_HEIGHT		= 0x00048003,			// Set physical screen width/heigh
	MB_TAG_SET_VIRTUAL_WIDTH_HEIGHT			= 0x00048004,			// Set virtual screen width/height
	MB_TAG_SET_COLOUR_DEPTH				= 0x00048005,			// Set screen colour depth
	MB_TAG_SET_PIXEL_ORDER				= 0x00048006,			// Set screen pixel order
	MB_TAG_SET_ALPHA_MODE				= 0x00048007,			// Set screen alpha mode
	MB_TAG_SET_VIRTUAL_OFFSET			= 0x00048009,			// Set screen virtual offset
	MB_TAG_SET_OVERSCAN				= 0x0004800A,			// Set screen overscan value
	MB_TAG_SET_PALETTE				= 0x0004800B,			// Set screen palette
	MB_TAG_SET_VSYNC				= 0x0004800E,			// Set screen VSync
	MB_TAG_SET_BACKLIGHT				= 0x0004800F,			// Set screen backlight

	/* VCHIQ commands */
	MB_TAG_VCHIQ_INIT				= 0x00048010,			// Enable VCHIQ

	/* Config commands */
	MB_TAG_GET_COMMAND_LINE				= 0x00050001,			// Get command line 

	/* Shared resource management commands */
	MB_TAG_GET_DMA_CHANNELS				= 0x00060001,			// Get DMA channels

	/* Cursor commands */
	MB_TAG_SET_CURSOR_INFO				= 0x00008010,			// Set cursor info
	MB_TAG_SET_CURSOR_STATE				= 0x00008011,			// Set cursor state
} TAG_CH_COMMAND;

/**********************************************************
 MAILBOX 
 *********************************************************/
typedef enum {
	MB_CH_POWER	= 0X0,		//power management
	MB_CH_FB	= 0X1,		//frame buffer
	MB_CH_VUART	= 0X2,		//virtual uart
	MB_CH_VCHIQ	= 0X3,		//vchiq
	MB_CH_LEDS	= 0X4,		//leds
	MB_CH_BTNS	= 0X5,		//buttons
	MB_CH_TOUCH	= 0X6,		//touchscreen
	MB_CH_COUNT	= 0X7,		//counter
	MB_CH_TAGS	= 0X8,		//tags (arm->vc)
	MB_CH_GPU	= 0X9		//gpu (vc->arm)
	
} MAILBOX_CHANNEL;

struct __attribute__((__packed__, aligned(4))) MailboxRegisters{
	const vuint32_t read0;		//0x00 read data from vc->arm
	uint32_t 	unused[3];	//0x04-0x0f
	vuint32_t 	peek0;		//0x10
	vuint32_t 	sender0;	//0x14
	vuint32_t 	status0;	//0x18 status of vc->arm
	vuint32_t 	config0;	//0x1c
	vuint32_t 	write1;		//0x20 write data from arm->vc
	uint32_t 	unused2[3];	//0x24-0x2f
	vuint32_t 	peek1;		//0x30
	vuint32_t 	sender1;	//0x34
	vuint32_t 	status1;	//0x38
	vuint32_t 	config1;	//0x3c
};

#define MAILBOX ((volatile __attribute__((aligned(4))) struct MailboxRegisters*)(uintptr_t)(PERIPHERAL_BASE + 0xb880))

void mailbox_write(uint32_t * message, MAILBOX_CHANNEL channel);
uint32_t mailbox_read(MAILBOX_CHANNEL channel);
bool mailbox_tag_message(uint32_t * response_buffer, uint8_t data_count, ...);

#endif
