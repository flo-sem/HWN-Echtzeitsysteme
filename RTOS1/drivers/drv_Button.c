#include "drv_Button.h"
#include "stm32f4xx.h"
#include <stddef.h>

void (*func_ptr_CB_pressed) (void) = NULL;
void (*func_ptr_CB_released) (void) = NULL;
uint16_t exti0_value = 0;

void drv_button_init(void) {
	RCC->AHB1ENR |= (1<<0);			// Taktversorgung für Port A
	EXTI->IMR |= (1<<0);			// EXTI0 Maskierung aufheben
	EXTI->RTSR |= (1<<0);			// EXTI0 auf steigende Flanke setzen
	EXTI->FTSR |= (1<<0);
	
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable NVIC for EXTI0 (NVIC für EXTI0 aktivieren)
    NVIC_SetPriority(EXTI0_IRQn, 1); // Set priority of EXTI0 to 1 (Priorität von EXTI0 auf 1 setzen)
}

void drv_button_CB_pressed_init(void (*callback)(void)){
	if (callback != NULL){             // Prüft auf einen validen Callback      
        func_ptr_CB_pressed = callback;
	}
}

void drv_button_CB_released_init(void (*callback)(void)){
	if (callback != NULL) {            // Prüft auf einen validen Callback 
        func_ptr_CB_released = callback;
    }
}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) { // Check if EXTI0 interrupt occurred (Überprüfen, ob EXTI0-Interrupt aufgetreten ist)
		if(exti0_value == 0){
			exti0_value = 1;
			if(func_ptr_CB_pressed != NULL){
			func_ptr_CB_pressed(); // Execute initalized CB function if it was set.
			}
		}
		else if(exti0_value == 1){
			exti0_value = 0;
			if(func_ptr_CB_released != NULL){
				func_ptr_CB_released();
			}
		}
		EXTI->PR |= EXTI_PR_PR0; // Clear EXTI0 pending flag (EXTI0-Pending-Flag löschen)
    }
}
