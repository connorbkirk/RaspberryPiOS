#include "types.h"
#include "act.h"
#include "gfx.h"

void wait(){
	int c = 0xf0000;
	while(c-- > 0);
}

int main(void){
	int i;
	char spin[4] = {'|', '/', '-', '\\' };

	for(i = 0; i < 5; i++){	
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	}

	console_init();
	
	console_write('H');
	console_write('E');
	console_write('L');
	console_write('L');
	console_write('O');
	console_write(' ');
	console_write('W');
	console_write('O');
	console_write('R');
	console_write('L');
	console_write('D');
	console_write('\n');

	while(1){
		i = i % 4;
		console_write(spin[i]);
		i++;
	}
}
