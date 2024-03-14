/* Include System Libaries */
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

/* Include Drivers */
#include "drivers/drv_Button.h"
#include "drivers/drv_LED.h"
#include "drivers/drv_Timer.h"

void ChangePWM() {
	// Button press = +10% PWM with overflow from 100% to 0% (Tastendruck = +10% PWM mit Überlauf von 100% auf 0%)
    e_pwm_value += e_pwm_increment;
    if (e_pwm_value > 100) {
        e_pwm_value = 0;
    }
    TIM4->CCR1 = e_pwm_value; // Update the PWM value (PWM-Wert aktualisieren)
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
	drv_timer4_init();
	drv_timer4_PWM(100, 10);
	
    while (1) {
        // Main program logic here (Hauptprogramm-Logik hier)
    }
}
