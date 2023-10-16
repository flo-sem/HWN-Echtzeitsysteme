//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt für Aufgabe 3
// 		Aufgaben:
//		-  User Button über Interrupt erkennen 				DONE
//		-  GPIOD & GPIOA Konfigurieren 						DONE
//		-  NVIC Konfigurieren 								DONE
//		-  ISR anlegen 										DONE
//		-  Interrupt sperren und freigeben 					DONE
//		-  Button-Event in statischer Variable speichern 	DONE
//		-  LED an und aus toggeln DONE

volatile static int state = 0;	//0=main , 1=interrupt

void EXTI0_IRQHandler() {
	//Deaktiviere Interrupt
	NVIC_DisableIRQ(EXTI0_IRQn);
	
	if(EXTI->PR & EXTI_PR_PR0) {
		++state;
		state=state%2;
		EXTI->PR |= EXTI_PR_PR0;
	}
}
int main() {
	RCC->AHB1ENR |= (1<<0);		// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);		// Taktversorgung für Port D

	GPIOD->MODER |= (1<<26);	//Setze GPIO 13 auf Output
		
	//EXTI für den Button
	EXTI->IMR |= EXTI_IMR_MR0;
	//Interrupt bei aufsteigender Flanke
	EXTI->RTSR |= EXTI_RTSR_TR0;
	
	//Konfiguriere NVIC für EXTI0
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn,0);
	
	//---MAIN LOOP---
	while (1) {
		//Aktiviere Interrupt
		NVIC_EnableIRQ(EXTI0_IRQn);
		
		//Logik zum toggeln der LED
		if(state == 0) GPIOD->BSRR |= (1<<13);
		else GPIOD->BSRR |= (1<<29);
	}

}