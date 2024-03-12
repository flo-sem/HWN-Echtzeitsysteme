//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt für Aufgabe 10
// Aufgaben: PWM-Steuerung der LED 4 mit dem User-Button

volatile static uint16_t pwmValue = 40;

void TIM4_Configuration() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock
    TIM4->CR1 |= TIM_CR1_CEN;           // Aktiviere Timer 4

    TIM4->PSC = 1600 - 1;  // Prescaler auf 1ms Basis setzen
    TIM4->ARR = 100 - 1;   // Auto-Reload Register auf 100 setzen (1ms)

    // Configure Capture/Compare Einheit 1 im PWM-Modus
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM mode 1
    TIM4->CCMR1 &= ~TIM_CCMR1_OC1M_0; // Clear OC1M bits

    TIM4->CCR1 = pwmValue; // Setze den PWM-Wert

    TIM4->CCER |= TIM_CCER_CC1E; // Enable Capture/Compare Channel 1

	TIM4->DIER &= ~TIM_DIER_UIE; // Disable update interrupt
}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) { // EXTI_PR wird 1 wenn der Interrupt ausgelöst wird
        EXTI->PR |= EXTI_PR_PR0;  // EXTI_PR wird zurückgesetzt, wenn eine 1 reingeschrieben wird

        // Tastendruck = +10% PWM mit Überlauf von 100% auf 0%
        pwmValue += 10;
        if (pwmValue > 100) {
            pwmValue = 0;
        }
        TIM4->CCR1 = pwmValue; // Aktualisiere den PWM-Wert
    }
}


int main() {

	RCC->AHB1ENR |= (1<<0);					// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);					// Taktversorgung für Port D

	//GPIOD->MODER |= (1<<26);				//Setze GPIO 13 auf Output

	EXTI->IMR |= (1<<0);					// EXTI0 Maskierung aufheben

	EXTI->RTSR |= (1<<0); 					// EXTI0 auf steigende Flanke setzen
	
	// Konfiguriere den GPIO-Pin (PD12) für alternative Funktion (AF2)
	GPIOD->AFR[1] |= (2 << 16);  // Alternative Funktion AF2 für PD12 (TIM4_CH1)

	// Konfiguriere PD12 (LED 4) für den alternativen Push-Pull-Modus
	GPIOD->MODER |= (2 << (2 * 12));  // Alternative Funktion (AF2) für PD12
	GPIOD->OTYPER &= ~(1 << 12);      // Push-Pull-Modus
	GPIOD->OSPEEDR |= (3 << (2 * 12)); // High-Speed
	
	// Aktiviere den Kanal 1 der Capture/Compare-Einheit
	TIM4->CCER |= TIM_CCER_CC1E;
	
	// Verknüpfe den GPIO-Pin (PD12) mit der Capture/Compare-Einheit 1 (TIM4_CH1)
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;  // CC1S = 01: CC1 Channel is configured as output

	
	/* NVIC SETUP */
	NVIC_EnableIRQ(EXTI0_IRQn);			//NVIC für EXTI0 einschalten
	NVIC_SetPriority(EXTI0_IRQn,1);	// Priorität von EXTI 0 auf null setzen
	
	TIM4_Configuration(); // Konfiguriere Timer 4 für PWM

	//---MAIN LOOP---
	while (1) {

	}
}
