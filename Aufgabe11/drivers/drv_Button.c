#include "drv_Button.h"
#include "stm32f4xx.h"
#include <stddef.h>

void drv_button_init(void) {
	RCC->AHB1ENR |= (1<<0);			// Taktversorgung für Port A
	EXTI->IMR |= (1<<0);			// EXTI0 Maskierung aufheben
	EXTI->RTSR |= (1<<0); 			// EXTI0 auf steigende Flanke setzen
	
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable NVIC for EXTI0 (NVIC für EXTI0 aktivieren)
    NVIC_SetPriority(EXTI0_IRQn, 1); // Set priority of EXTI0 to 1 (Priorität von EXTI0 auf 1 setzen)
}

void drv_button_CB_pressed_init(void (*callback)(void)){
	if (callback != NULL){             // Prüft auf einen validen Callback      
        callback();
	}
}

void drv_button_CB_released_init(void (*callback)(void)){
	if (callback != NULL) {            // Prüft auf einen validen Callback 
        callback();
    }
}
