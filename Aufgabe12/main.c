/* Includes */
#include "main.h"
#include "state_machine.h"
#include "drivers/drv_Timer.h"
#include "drivers/drv_LED.h"
#include "drivers/drv_Button.h"
#include <stdint.h>

uint32_t now = 0;
uint32_t oldTime = 0;

StateMachine myStateMachine;

uint32_t e_pwm_value;
uint32_t e_pwm_increment;

void setButtonPressed() {
	handleEvent(&myStateMachine, BUTTON_PRESS);
}

int main() {
	drv_led_init();
	drv_timer4_init();
	drv_button_init();
	drv_button_CB_pressed_init(setButtonPressed);
	initializeStateMachine(&myStateMachine);
    while (1) {
        //State machine
		switch(myStateMachine.current_state) {
			case RED:
				if (now - oldTime > 5000) {
					switchState(&myStateMachine, RED_YELLOW);
				}
				drv_led_OFF(13);
				drv_led_ON(14);
				break;
			case RED_YELLOW:
				if (now - oldTime > 2000) {
					switchState(&myStateMachine, GREEN);
				}
				drv_led_ON(13);
				drv_led_ON(14);
				break;
			case GREEN:
				if (now - oldTime > 7000) {
					switchState(&myStateMachine, YELLOW);
				}
				drv_led_ON(12);
				drv_led_OFF(13);
				drv_led_OFF(14);
				break;
			case YELLOW:
				if (now - oldTime > 2000) {
					if(myStateMachine.current_event == BUTTON_PRESS) {
						myStateMachine.current_event = NO_EVENT;
						switchState(&myStateMachine, RED_BLUE);
					}
					else {
						switchState(&myStateMachine, RED);
					}
				}
				drv_led_ON(13);
				drv_led_OFF(14);
				drv_led_OFF(12);
				break;
			case RED_BLUE:
				// PWM FREQUENZ =(now-oldTime )/ 10000
				if(now-oldTime > 10000) {
					switchState(&myStateMachine, RED);
				}
				setDutycycle(10000);
				drv_led_ON(14);
				drv_led_OFF(13);
				drv_led_OFF(12);
				break;
			
		}
    }
}
