#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

volatile static uint16_t pwmValue = 40;  // Variable für PWM-Wert

void TIM4_Configuration() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock (Timer 4 aktivieren)
    TIM4->CR1 |= TIM_CR1_CEN;           // Enable Timer 4 (Timer 4 aktivieren)

    TIM4->PSC = 1600 - 1;  // Set prescaler to 1600 (Prescaler auf 1600 setzen)
    TIM4->ARR = 100 - 1;   // Set auto-reload register to 100 (Auto-Reload Register auf 100 setzen)
	
	/* Ausführliche erklärung PSC und ARR :
	PSC: Prescaler
		Dieser bestimmt die "Basisezeit" des Timers. Dieser Wert entscheidet also, ob der Timer 
		in 1us, 100us, 1ms,... Schritten zählt
	
	Die Basiszeit ergibt sich aus:
		t_Basis = 1/f_clock * (PSC + 1)
		
	ARR: Auto reload register
		Dieses Register bestimmt, wie viele Zähleinheiten für eine vollständige PWM-Periode benötigt werden.
		Also ob der Zähler 100, 200, 1000, ... Basiszeiten zählen soll.
	
	Somit ergibt sich für die PWM-Periode:
		t_Periode =  1/f_clock * (PSC + 1) * (ARR + 1)
	
	Für diese Konfiguration ist die PWM-Periode 10ms bzw Frequenz 100Hz
	
	*/

    TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Set PWM mode 1 (PWM-Modus 1 setzen)
    TIM4->CCMR1 &= ~TIM_CCMR1_OC1M_0; // Clear OC1M bits (OC1M-Bits löschen)

    TIM4->CCR1 = pwmValue; // Set the PWM value (PWM-Wert setzen)

    TIM4->CCER |= TIM_CCER_CC1E; // Enable Capture/Compare Channel 1 (Capture/Compare Kanal 1 aktivieren)

    TIM4->DIER &= ~TIM_DIER_UIE; // Disable update interrupt (Update-Interrupt deaktivieren)
}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) { // Check if EXTI0 interrupt occurred (Überprüfen, ob EXTI0-Interrupt aufgetreten ist)
        EXTI->PR |= EXTI_PR_PR0;  // Clear EXTI0 pending flag (EXTI0-Pending-Flag löschen)

        // Button press = +10% PWM with overflow from 100% to 0% (Tastendruck = +10% PWM mit Überlauf von 100% auf 0%)
        pwmValue += 10;
        if (pwmValue > 100) {
            pwmValue = 0;
        }
        TIM4->CCR1 = pwmValue; // Update the PWM value (PWM-Wert aktualisieren)
    }
}

int main() {
    RCC->AHB1ENR |= (1 << 3); // Enable GPIO D clock (GPIO D-Takt aktivieren)
    
    EXTI->IMR |= (1 << 0); // Enable EXTI0 interrupt (EXTI0-Interrupt aktivieren)
    EXTI->RTSR |= (1 << 0); // Set EXTI0 to rising edge trigger (EXTI0 auf steigende Flanke setzen)

    // Konfiguriere den GPIO-Pin (PD12) für alternative Funktion (AF2)
    GPIOD->AFR[1] |= (2 << 16);  // Set alternative function AF2 for PD12 (Alternative Funktion AF2 für PD12 setzen)

    // Konfiguriere PD12 (LED 4) für den alternativen Push-Pull-Modus
    GPIOD->MODER |= GPIO_MODER_MODE12_1;  // Set alternative function (AF2) for PD12 (Alternative Funktion AF2 für PD12 setzen)
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT12;   // Set Push-Pull mode (Push-Pull-Modus setzen)
    GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED12_1 | GPIO_OSPEEDR_OSPEED12_0; // Set High-Speed (High-Speed setzen)

    NVIC_EnableIRQ(EXTI0_IRQn); // Enable NVIC for EXTI0 (NVIC für EXTI0 aktivieren)
    NVIC_SetPriority(EXTI0_IRQn, 1); // Set priority of EXTI0 to 1 (Priorität von EXTI0 auf 1 setzen)

    TIM4_Configuration(); // Configure Timer 4 for PWM (Timer 4 für PWM konfigurieren)

    while (1) {
        // Main program logic here (Hauptprogramm-Logik hier)
    }
}
