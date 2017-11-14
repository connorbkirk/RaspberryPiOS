#include "types.h"
#include "mailbox.h"
#include <stdarg.h>

#define FULL 0x80000000
#define EMPTY 0x40000000

void mailbox_write(uint32_t * message_addr, MAILBOX_CHANNEL channel){
	uint32_t status;
	uintptr_t message = (uintptr_t)message_addr;

	//message |= 0xC0000000;//bus mask

        do{
                status = MAILBOX->status1;
        }while( (status & FULL) != 0 );

	message &= ~(0xF);
	message |= channel;

	MAILBOX->write1 = (vuint32_t)message;
}

uint32_t mailbox_read(MAILBOX_CHANNEL channel){
	uint32_t status;
	uint32_t mail;
	
	do{
		do{
			status = MAILBOX->status0;	
		}while( (status & EMPTY) != 0);

		mail = MAILBOX->read0;
		
	}while( (mail & 0b1111) != channel );

	return mail & ~(0xF);
}

/*
 * This will post and execute the given variadic data onto the 
 * tags channel of the mailbox system.
 *
 * response_buffer will store the response data
 * data_count is the number of variadic vars
 * response_buffer can be NULL if no response is needed
 *
 * Returns true for success
 * false for failure and response_buffer is untouched
 *
 */
bool mailbox_tag_message(uint32_t * response_buffer, uint8_t data_count, ...){
	int i;

	uint32_t __attribute__((aligned(16))) message[32];
	va_list list;
	va_start(list, data_count);
	message[0] = (data_count + 3)*4;	//size of message
	message[data_count+2] = 0;		//set end to 0
	message[1] = 0;				//0 response message
	for(i = 0; i < data_count; i++){	//set variadic
		message[2+i] = va_arg(list, uint32_t);
	}
	va_end(list);

	mailbox_write(message, MB_CH_TAGS);
	mailbox_read(MB_CH_TAGS);

	if(message[1] == FULL){
		if(response_buffer){
			for(i = 0; i < data_count; i++){
				response_buffer[i] = message[2 + i];
			}
		}
		return true;
	}

	return false;
}
