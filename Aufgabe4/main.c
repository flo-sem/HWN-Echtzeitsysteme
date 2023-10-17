//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
//---HEADER---
#include "main.h"
// Projekt f�r Aufgabe 3
// 		Aufgaben:
//		- 	Effiziente FIFO Struktur implementieren
//		-   Aufgabe 3 von Taster Event auf FIFO umbauen


void delay (int time) {
	for (int i=0; i<10000*time; ++i) {}		
}

void EXTI0_IRQHandler() {
	// Auch m�lich: NVIC->ICER[0] |= (1<<6);
	if(EXTI->PR & EXTI_PR_PR0) {		// EXTI_PR wird 1 wenn der Interrupt ausgel�st wird

		EXTI->PR |= EXTI_PR_PR0;			// EXTI_PR wird zur�ckgesetzt, wenn eine 1 reingeschrieben wird
	}
}



int main() {
	RCC->AHB1ENR |= (1<<0);					// Taktversorgung f�r Port A
	RCC->AHB1ENR |= (1<<3);					// Taktversorgung f�r Port D

	GPIOD->MODER |= (1<<26);				//Setze GPIO 13 auf Output

	EXTI->IMR |= (1<<0);						// EXTI0 Maskierung aufheben

	EXTI->RTSR |= (1<<0); 					// EXTI0 auf steigende Flanke setzen
	
	
	NVIC_EnableIRQ(EXTI0_IRQn);			//NVIC f�r EXTI0 einschalten
	// Oder: NVIC->ISER[0] |= (1<<6);
	
	NVIC_SetPriority(EXTI0_IRQn,0);	// Priorit�t von EXTI 0 auf null setzen
	// Oder: NVIC->IP[4*6] |= (0<<0);
	
	//---MAIN LOOP---
	while (1) {
		NVIC_EnableIRQ(EXTI0_IRQn);		//NVIC f�r EXTI0 einschalten
		// Oder: NVIC->ISER[0] |= (1<<6);
		delay(5);
		//Logik zum toggeln der LED
		if(1) {
			GPIOD->BSRR |= (1<<13);
		}
		else {
			GPIOD->BSRR |= (1<<29);
		}
	}

}