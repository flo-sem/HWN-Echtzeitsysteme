/* Includes */
#include "state_machine.h"
#include "drivers/drv_Timer.h"

void initializeStateMachine(StateMachine *machine) {
    machine->current_state = RED;
	machine->current_event = NO_EVENT;
}

void handleEvent(StateMachine *machine, Event event) {
	machine->current_event = event;
}

void switchState(StateMachine *machine, State state) {
	machine->current_state = state;
	oldTime = getCurrentTime();
}
