//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt für Aufgabe 6
// 		Aufgaben:
//		-  TIM4 soll jetzt einen Interrupt auslösen
//		-  Interrup in main bearbeiten

volatile static int state = 0;	
//event
volatile static int e_timer = 0;

//trace variablen
volatile static int t_buttonInterrupt = 0;
volatile static int t_timerInterrupt = 0;


void delay (int time) {
	for (int i=0; i<10000*time; ++i) {}		
}


void TIM4_Configuration() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock
	TIM4->CR1 |= TIM_CR1_CEN; // Aktiviere Timer 4

    TIM4->PSC = 16000 - 1 ; // Prescaler auf 1ms basis setzen
    TIM4->ARR = 1000 - 1; // Mit Auto-Reload Register 1s perioden festlegen

	TIM4->DIER |= TIM_DIER_UIE; // Zur verwendung des Interrupts
}

void EXTI0_IRQHandler() {
	t_timerInterrupt = 0;
	t_buttonInterrupt = 1;
    if (EXTI->PR & EXTI_PR_PR0) { // EXTI_PR wird 1 wenn der Interrupt ausgelöst wird
        ++state;
        state = state % 2;
        EXTI->PR |= EXTI_PR_PR0;  // EXTI_PR wird zurückgesetzt, wenn eine 1 reingeschrieben wird
    }
	delay(10);
	t_timerInterrupt = 0;
	t_buttonInterrupt = 0;
}

void TIM4_IRQHandler() {
	t_timerInterrupt = 1;
	t_buttonInterrupt = 0;

    if (TIM4->SR & TIM_SR_UIF) {		
		e_timer = 1;
        TIM4->SR &= ~TIM_SR_UIF; // Clear UIF
    }
	delay(10);
	t_timerInterrupt = 0;
	t_buttonInterrupt = 0;
}



int main() {
	t_timerInterrupt = 0;
	t_buttonInterrupt = 0;
	TIM4_Configuration();

	RCC->AHB1ENR |= (1<<0);					// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);					// Taktversorgung für Port D

	GPIOD->MODER |= (1<<26);				//Setze GPIO 13 auf Output

	EXTI->IMR |= (1<<0);					// EXTI0 Maskierung aufheben

	EXTI->RTSR |= (1<<0); 					// EXTI0 auf steigende Flanke setzen
	
	/* NVIC SETUP */
	NVIC_EnableIRQ(EXTI0_IRQn);			//NVIC für EXTI0 einschalten
	NVIC_SetPriority(EXTI0_IRQn,1);	// Priorität von EXTI 0 auf null setzen
	
	NVIC_EnableIRQ(TIM4_IRQn); // NVIC für TIM4 einschalten
    NVIC_SetPriority(TIM4_IRQn, 0); // Priorität von TIM4 auf eins setzen (geringer als EXTI0)
	
	int blink = 0;

	//---MAIN LOOP---
	while (1) {
		if(state == 0 ){
			if(e_timer){
				if(blink == 0){
					blink = 1;
					GPIOD->BSRR |= (1<<29);
				}else{
					blink = 0;
					GPIOD->BSRR |= (1<<13);
				}
				e_timer = 0;
			} 
		} else {
			GPIOD->BSRR |= (1<<29);
		}
	}
}
