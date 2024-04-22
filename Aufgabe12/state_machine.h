/* Define the different States */ 
typedef enum {
	RED, RED_YELLOW, GREEN, YELLOW, RED_BLUE
} State;

typedef enum {
    BUTTON_PRESS,
	TIME_UP
} Event;

// Define state machine structure
typedef struct {
    State current_state;
	Event current_event;
} StateMachine;

/* Function prototypes */
void initializeStateMachine(StateMachine *machine);
void handleEvent(StateMachine *machine, Event event);