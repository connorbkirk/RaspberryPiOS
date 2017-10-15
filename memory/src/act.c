#include "types.h"
#include "act.h"
#include "mailbox.h"

void set_act_state(uint32_t state){

	uint32_t __attribute__((aligned(16))) message[8];
        message[0] = sizeof(message);			//total message size
        message[1] = 0;					//zero response message
        message[2] = MB_TAG_SET_GPIO_STATE;		//set gpio state
        message[3] = 8;					//response is 8 bytes
        message[4] = 8;					//send params is 8 bytes
        message[5] = 130;				//port 130
        message[6] = state;				//set on/off
        message[7] = 0;					//END

	mailbox_write(message, MB_CH_TAGS);

	mailbox_read(MB_CH_TAGS);
}
