//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt f�r Aufgabe 3
// 		Aufgaben:
//		-  User Button �ber Interrupt erkennen DONE
//		-  GPIOD & GPIOA Konfigurieren DONE
//		-  NVIC Konfigurieren DONE
//		-  ISR anlegen DONE
//		-  Interrupt sperren und freigeben
//		-	 Button-Event in statischer Variable speichern
//		-	 LEDs PD13-15 bei gedr�cktem Taster *hoch*,
//			 bei nicht gedr�cktem Taster *runter* z�hlen

void EXTI0_IRQHandler() {
	//Deaktiviere Interrupt
	NVIC_DisableIRQ(EXTI0_IRQn);
	
	if(EXTI->PR & EXTI_PR_PR0) {
		volatile int i = 555;
		EXTI->PR |= EXTI_PR_PR0;
	}
}
int main() {
	RCC->AHB1ENR |= (1<<0);		// Taktversorgung f�r Port A
	RCC->AHB1ENR |= (1<<3);		// Taktversorgung f�r Port D
	
	//GPIOA->Moder... nicht ben�tigt, da Input Port
	//GPIOD->MODER |= (1<<24);	//Setze GPIO 12 auf Output
	GPIOD->MODER |= (1<<26);	//Setze GPIO 13 auf Output
	GPIOD->MODER |= (1<<28);	//Setze GPIO 14 auf Output
	GPIOD->MODER |= (1<<30);	//Setze GPIO 15 auf Output
	
	//Einstellen der Clock f�r GPIOA und SYSCFG Peripherals
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	//GPIO (PA0) auf Input
	GPIOA->MODER &= ~(0x3 << (0 * 2));
	
	//EXTI f�r den Button
	EXTI->IMR |= EXTI_IMR_MR0;
	//Interrupt bei aufsteigender Flanke
	EXTI->RTSR |= EXTI_RTSR_TR0;
	
	//Verbinde EXTI mit GPIO
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	
	//Konfiguriere NVIC f�r EXTI0
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn,0);
	
	//---MAIN LOOP---
	while (1) {
		//Aktiviere Interrupt
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
}