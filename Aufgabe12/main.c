/* Includes */
#include "main.h"
#include "state_machine.h"
#include "drivers/drv_Timer.h"
#include <stdint.h>

uint32_t buttonPressed = 0;
uint32_t now = 0;
uint32_t oldTime = 0;

uint32_t e_pwm_value;
uint32_t e_pwm_increment;

void setButtonPressed() {
	buttonPressed = 1;
}

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
				// PWM FREQUENZ =(now-oldTime )/ 10000
				if(now-oldTime > 10000) {
					switchState(&myStateMachine, RED);
				}
				break;
			
		}
    }
}
