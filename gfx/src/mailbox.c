#include "types.h"
#include "mailbox.h"

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
