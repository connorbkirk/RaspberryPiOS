#include "types.h"
#include "act.h"
#include "gfx.h"

void wait(){
	int c = 0xf0000;
	while(c-- > 0);
}

int main(void){
	int i;
//	char spin[4] = {'|', '/', '-', '\\' };

	for(i = 0; i < 5; i++){	
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	}

	console_init();

	wait();
	wait();

	console_test();
	wait();
	wait();
	
	console_write('H');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('E');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('L');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('L');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('O');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write(' ');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('W');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('O');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('R');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('L');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('D');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	console_write('\n');
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();


	while(1);

}
