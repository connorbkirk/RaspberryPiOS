#include "types.h"
#include "act.h"

void wait(){
	int c = 0xf0000;
	while(c-- > 0);
}

int main(void){
	while(1){
		set_act_state(1);
		wait();
		set_act_state(0);
		wait();
	}
}
