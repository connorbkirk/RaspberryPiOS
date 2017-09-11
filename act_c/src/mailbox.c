#include "types.h"

#define MAILBOX 0x3f00b880
#define FULL 0x80000000
#define EMPTY 0x40000000
#define W_OFFSET 0x20
#define STATUS_OFFSET 0x18

void mailbox_write(void * message, uint32_t channel){
	vuint32_t status;

        do{
                status = READ32((MAILBOX + STATUS_OFFSET));
        }while( (status & FULL) != 0 );

	message += channel;

	WRITE32(MAILBOX + W_OFFSET, message);
}

uint32_t mailbox_read(uint32_t channel){
	vuint32_t status;
	uint32_t mail;
	
	do{
		do{
			status = READ32((MAILBOX + STATUS_OFFSET));
		}while( (status & EMPTY) != 0);

		mail = READ32(MAILBOX);
		
	}while( (mail & 0b1111) != channel );

	return mail;
}
