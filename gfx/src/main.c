#include "types.h"
#include "act.h"
#include "gfx.h"

void wait(){
	int c = 0xf0000;
	while(c-- > 0);
}

int main(void){
	int i;

	for(i = 0; i < 5; i++){	
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	}

	console_init();

	wait();
	wait();

//	console_test();
//	wait();
//	wait();
	
	console_write("Hello world", 11);

	while(1);

}
