//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

//---HEADER---
#include "main.h"
// Projekt für Aufgabe 3
// 		Aufgaben:
//		- 	Effiziente FIFO Struktur implementieren
//		-   Aufgabe 3 von Taster Event auf FIFO umbauen

int shift_write = 0;
int shift_read = 0;
int FIFO_List[100];

void delay (int time) {
	for (int i=0; i<10000*time; ++i) {}		
}

void executeInterrupt() {
	GPIOD->BSRR |= (1<<29);
	delay(80);
}

void EXTI0_IRQHandler() {
	// Auch m�lich: NVIC->ICER[0] |= (1<<6);
	if(EXTI->PR & EXTI_PR_PR0) {		// EXTI_PR wird 1 wenn der Interrupt ausgel�st wird
		*(FIFO_List+(shift_write%100)) = 1;
		shift_write++;
		EXTI->PR |= EXTI_PR_PR0;			// EXTI_PR wird zur�ckgesetzt, wenn eine 1 reingeschrieben wird
	}
}


int main() {
	RCC->AHB1ENR |= (1<<0);					// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);					// Taktversorgung für Port D

	GPIOD->MODER |= (1<<26);				//Setze GPIO 13 auf Output

	EXTI->IMR |= (1<<0);						// EXTI0 Maskierung aufheben

	EXTI->RTSR |= (1<<0); 					// EXTI0 auf steigende Flanke setzen
	
	
	NVIC_EnableIRQ(EXTI0_IRQn);			//NVIC für EXTI0 einschalten
	// Oder: NVIC->ISER[0] |= (1<<6);
	
	NVIC_SetPriority(EXTI0_IRQn,0);	// Priorität von EXTI 0 auf null setzen
	// Oder: NVIC->IP[4*6] |= (0<<0);	
	
	
	//---MAIN LOOP---
	while (1) {
		NVIC_EnableIRQ(EXTI0_IRQn);		//NVIC für EXTI0 einschalten
		// Oder: NVIC->ISER[0] |= (1<<6);
		if(*(FIFO_List+(shift_read%100)) == 1) {
			executeInterrupt();
			*(FIFO_List+(shift_read%100)) = 0;
			shift_read++;
		}
		else {
			GPIOD->BSRR |= (1<<13);
		}
		GPIOD->BSRR |= (1<<13);

	}

}