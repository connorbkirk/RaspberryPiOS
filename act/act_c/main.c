typedef volatile unsigned int vuint32_t;

#define READ32(addr) (*(vuint32_t*)addr)
#define WRITE32(addr, val) (*(vuint32_t*)(addr) = (vuint32_t)(val))

#define MAILBOX 0x3f00b880

struct body{
	vuint32_t sz;//hardcoded for now
	vuint32_t req_code;
	vuint32_t tag_id;
	vuint32_t val_size;
	vuint32_t resp_size;
	vuint32_t pin_no;
	vuint32_t pin_state;
	vuint32_t end;
} __attribute__((aligned(16))) body;

int main(void){
	/*uint32_t body[8] __attribute__((aligned(4)));
	body[0] = sizeof(body);
	body[1] = 0;
	body[2] = 0x00038041;
	body[3] = 8;
	body[4] = 0;
	body[5] = 130;
	body[6] = 1;
	body[7] = 0;*/

	struct body b;
	b.sz = 32;
	b.req_code = 0;
	b.tag_id = 0x00038041;
	b.val_size = 8;
	b.resp_size = 0;
	b.pin_no = 130;
	b.pin_state = 1;
	b.end = 0;

	vuint32_t status; 
	
	do{   
		status = READ32(MAILBOX + 0x18);
	}while( (status & 0x80000000) != 0 );

	volatile void* msg = &b;
	msg = msg + 8;

	WRITE32(MAILBOX + 0x20, (vuint32_t*)msg);

	while(1);
}
