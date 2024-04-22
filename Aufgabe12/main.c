/* Includes */
#include "main.h"
#include "state_machine.h"
#include "drivers/drv_Timer.h"

int main() {
	StateMachine myStateMachine;
	initializeStateMachine(&myStateMachine);
    while (1) {
        //State machine
		switch(myStateMachine.current_state) {
			case RED:
				if (now - oldTime > 5000) {
					switchState(&myStateMachine, RED_YELLOW);
				}
				break;
			case RED_YELLOW:
				if (now - oldTime > 2000) {
					switchState(&myStateMachine, GREEN);
				}
				break;
			case GREEN:
				if (now - oldTime > 7000) {
					switchState(&myStateMachine, YELLOW);
				}
				break;
			case YELLOW:
				if (now - oldTime > 2000) {
					if(myStateMachine.current_event == BUTTON_PRESS) {
						myStateMachine.current_event = NO_EVENT;
						switchState(&myStateMachine, RED_BLUE);
					}
					switchState(&myStateMachine, RED);
				}
				break;
			case RED_BLUE:
				if(now-oldTime > 10000) {
					switchState(&myStateMachine, RED);
				}
				break;
			
		}
    }
}
