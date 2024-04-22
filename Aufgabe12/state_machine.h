#include "stm32f4xx.h"

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

uint32_t oldTime;

/* Function prototypes */
void initializeStateMachine(StateMachine *machine);
void handleEvent(StateMachine *machine, Event event);
void switchState(StateMachine *machine, State state);
