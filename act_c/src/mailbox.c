#include "types.h"
#include "basic-hw.h"

#define FULL 0x80000000
#define EMPTY 0x40000000

void mailbox_write(uint32_t message, MAILBOX_CHANNEL channel){
	uint32_t status;

        do{
                status = MAILBOX->status1;
        }while( (status & FULL) != 0 );

	message += channel;
	
	MAILBOX->write1 = message;
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

	return mail;
}
