/* Includes */
#include "state_machine.h"

void initializeStateMachine(StateMachine *machine) {
    machine->current_state = RED;
}

void handleEvent(StateMachine *machine, Event event) {
	machine->current_event = event;
}