#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "stm32f4xx.h"

extern uint32_t oldTime;

/* Define the different States */ 
typedef enum {
	RED, RED_YELLOW, GREEN, YELLOW, RED_BLUE
} State;

typedef enum {
	NO_EVENT,
    BUTTON_PRESS
} Event;

// Define state machine structure
typedef struct {
    State current_state;
	Event current_event;
} StateMachine;


/* Function prototypes */
void initializeStateMachine(StateMachine *machine);
void handleEvent(StateMachine *machine, Event event);
void switchState(StateMachine *machine, State state);

#endif //STATE_MACHINE_H