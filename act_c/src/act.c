#include "types.h"
#include "act.h"
#include "mailbox.h"

#define ACT_CHANNEL 8

struct msg_body{
        vuint32_t sz;
        vuint32_t req_code;
        vuint32_t tag_id;
        vuint32_t val_size;
        vuint32_t resp_size;
        vuint32_t pin_no;
        vuint32_t pin_state;
        vuint32_t end;
} __attribute__((aligned(16)));

void set_act_state(uint32_t state){
	struct msg_body body;
        body.sz = 32;
        body.req_code = 0;
        body.tag_id = 0x00038041;
        body.val_size = 8;
        body.resp_size = 0;
        body.pin_no = 130;
        body.pin_state = state;
        body.end = 0;

	mailbox_write(&body, ACT_CHANNEL);

	mailbox_read(ACT_CHANNEL);
}
