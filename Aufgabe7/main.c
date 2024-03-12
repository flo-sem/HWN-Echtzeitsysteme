//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt für Aufgabe 7
// 		Aufgaben:
//		  - LED 4 (PD12) über alternative Portfunktion des Compare-Registers CCR1 blinken lassen

void TIM4_Configuration() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock
	TIM4->CR1 |= TIM_CR1_CEN; 			// Aktiviere Timer 4

    TIM4->PSC = 16000 - 1 ; 			// Prescaler auf 1ms basis setzen
    TIM4->ARR = 1000 - 1; 				// Mit Auto-Reload Register 1s perioden festlegen

	// Configure Capture/Compare Einheit 1 auf Compare- und Toggle-Modus
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; // Toggle-Modus

    // Setzen des Compare-Werts (Toggle-Wert)
    TIM4->CCR1 = 500; // Beispielwert (50% der Periode)
	
	// Aktiviere den alternativen Ausgangspin für CCR1 (LED 4)
    TIM4->CCER |= TIM_CCER_CC1E;  // CC1E für Enable,

}


int main() {
	TIM4_Configuration();

	RCC->AHB1ENR |= (1<<3);					// Taktversorgung für Port D

	GPIOD->MODER |= (1<<25);				//Setze GPIO 12 auf Output
	GPIOD->AFR[1] |= 0x2 << 16; 			// Alternative Funktion 2 für PD12 (TIM4_CH1)

	//---MAIN LOOP---
	while (1) {

	}
}
