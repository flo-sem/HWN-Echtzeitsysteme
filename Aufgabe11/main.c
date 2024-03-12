/* Include System Libaries */
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

/* Include Drivers */
#include "drivers/drv_Button.h"
#include "drivers/drv_LED.h"
#include "drivers/drv_Timer.h"
volatile static uint16_t pwmValue = 40;  // Variable für PWM-Wert

void TIM4_Configuration() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock (Timer 4 aktivieren)
    TIM4->CR1 |= TIM_CR1_CEN;           // Enable Timer 4 (Timer 4 aktivieren)

    TIM4->PSC = 1600 - 1;  // Set prescaler to 1600 (Prescaler auf 1600 setzen)
    TIM4->ARR = 100 - 1;   // Set auto-reload register to 100 (Auto-Reload Register auf 100 setzen)

    TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Set PWM mode 1 (PWM-Modus 1 setzen)
    TIM4->CCMR1 &= ~TIM_CCMR1_OC1M_0; // Clear OC1M bits (OC1M-Bits löschen)

    TIM4->CCR1 = pwmValue; // Set the PWM value (PWM-Wert setzen)

    TIM4->CCER |= TIM_CCER_CC1E; // Enable Capture/Compare Channel 1 (Capture/Compare Kanal 1 aktivieren)

    TIM4->DIER &= ~TIM_DIER_UIE; // Disable update interrupt (Update-Interrupt deaktivieren)
}

void ChangePWM() {
	// Button press = +10% PWM with overflow from 100% to 0% (Tastendruck = +10% PWM mit Überlauf von 100% auf 0%)
    pwmValue += 10;
    if (pwmValue > 100) {
        pwmValue = 0;
    }
    TIM4->CCR1 = pwmValue; // Update the PWM value (PWM-Wert aktualisieren)
}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) { // Check if EXTI0 interrupt occurred (Überprüfen, ob EXTI0-Interrupt aufgetreten ist)
        EXTI->PR |= EXTI_PR_PR0;  // Clear EXTI0 pending flag (EXTI0-Pending-Flag löschen)
		drv_button_CB_pressed_init(ChangePWM);
    }
}


int main() {
	drv_led_init();
    drv_button_init();

    TIM4_Configuration(); // Configure Timer 4 for PWM (Timer 4 für PWM konfigurieren)
	
    while (1) {
        // Main program logic here (Hauptprogramm-Logik hier)
    }
}
