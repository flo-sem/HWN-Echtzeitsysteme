#include "drv_Button.h"
#include "stm32f4xx.h"
#include <stddef.h>

void drv_button_init(void) {
	RCC->AHB1ENR |= (1<<0);			// Taktversorgung für Port A
	EXTI->IMR |= (1<<0);			// EXTI0 Maskierung aufheben
	EXTI->RTSR |= (1<<0); 			// EXTI0 auf steigende Flanke setzen
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
