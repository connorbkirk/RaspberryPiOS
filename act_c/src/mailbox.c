#include "types.h"

#define MAILBOX 0x3f00b880
#define FULL 0x80000000
#define W_OFFSET 0x20

void mailbox_write(void * message, vuint32_t channel){
	vuint32_t status;

        do{
                status = READ32(MAILBOX + 0x18);
        }while( (status & FULL) != 0 );

	message += channel;

	WRITE32(MAILBOX + W_OFFSET, message);
}
