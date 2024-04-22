/* Include Drivers */
#include "drivers/drv_Button.h"
#include "drivers/drv_LED.h"
#include "drivers/drv_Timer.h"

uint32_t e_pwm_value = 0;  // global variable for current pwm value
uint32_t e_pwm_increment = 0; // global variable for the pwm incrementation

void IncreasePWM() {
	// Button press = +10% PWM with overflow from 100% to 0% (Tastendruck = +10% PWM mit Überlauf von 100% auf 0%)
    e_pwm_value += e_pwm_increment;
    if (e_pwm_value > 100) {
        e_pwm_value = 0;
    }
}


int main() {
	drv_led_init();
    drv_button_init();
	drv_button_CB_pressed_init(IncreasePWM);
	drv_timer4_init();
	drv_timer4_PWM(100, 10);
	
    while (1) {
        // Main program logic here (Hauptprogramm-Logik hier)
    }
}
