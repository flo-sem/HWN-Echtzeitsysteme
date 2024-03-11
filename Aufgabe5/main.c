//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt für Aufgabe 5
// 		Aufgaben:
//		-  delay Funktion durch Timer ersetzen
//		-  TIM4 verwenden
//		-  TIM4 nach vorgaben konfigurieren

volatile static int state = 0;	//0=main , 1=interrupt

void TIM4_Configuration() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock
	TIM4->CR1 |= TIM_CR1_CEN; // Aktiviere Timer 4

    TIM4->PSC = 16000 - 1 ; // Prescaler auf 1ms basis setzen
    TIM4->ARR = 1000 - 1; // Mit Auto-Reload Register 500ms perioden festlegen

}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) { // EXTI_PR wird 1 wenn der Interrupt ausgelöst wird
        ++state;
        state = state % 2;
        EXTI->PR |= EXTI_PR_PR0;  // EXTI_PR wird zurückgesetzt, wenn eine 1 reingeschrieben wird
    }
}



int main() {
	TIM4_Configuration();

	RCC->AHB1ENR |= (1<<0);					// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);					// Taktversorgung für Port D

	GPIOD->MODER |= (1<<26);				//Setze GPIO 13 auf Output

	EXTI->IMR |= (1<<0);					// EXTI0 Maskierung aufheben

	EXTI->RTSR |= (1<<0); 					// EXTI0 auf steigende Flanke setzen
	
	
	NVIC_EnableIRQ(EXTI0_IRQn);			//NVIC für EXTI0 einschalten
	// Oder: NVIC->ISER[0] |= (1<<6);
	int blink = 0;
	NVIC_SetPriority(EXTI0_IRQn,0);	// Priorität von EXTI 0 auf null setzen
	// Oder: NVIC->IP[4*6] |= (0<<0);
	//---MAIN LOOP---
	while (1) {
		if(state == 0 ){
			if(TIM4->SR & TIM_SR_UIF){
				if(blink == 0){
					blink = 1;
					GPIOD->BSRR |= (1<<29);
				}else{
					blink = 0;
					GPIOD->BSRR |= (1<<13);
				}
				TIM4->SR &= ~(TIM_SR_UIF); // Clear UIF
			} 
		} else {
			GPIOD->BSRR |= (1<<29);
		}
	}
}
