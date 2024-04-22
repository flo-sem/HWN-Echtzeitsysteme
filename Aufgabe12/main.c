/* Includes */
#include "main.h"
#include "state_machine.h"


int main() {
	StateMachine myStateMachine;
	initializeStateMachine(&myStateMachine);
    while (1) {
        //State machine
		switch(myStateMachine.current_state) {
			case RED:
				if (
				break;
			case RED_YELLOW:
				break;
			case GREEN:
				break;
			case YELLOW:
				break;
			case RED_BLUE:
				break;
			
		}
    }
}
