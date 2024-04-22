/* Includes */
#include "state_machine.h"

void initializeStateMachine(StateMachine *machine) {
    machine->current_state = RED;
}

void handleEvent(StateMachine *machine, Event event) {
	machine->current_event = event;
}

void switchState(StateMachine *machine, State state) {
	machine->current_state = state;
}

int calcTime() {
	return 0;
}