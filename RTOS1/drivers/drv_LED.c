#include "drv_LED.h"
#include "stm32f4xx.h"

void drv_led_init(void) {
    RCC->AHB1ENR |= (1 << 3);	// Taktversorgung für Port D
	//GPIOD->MODER |= (1 << 24);  //Setze GPIO 12 auf Output
	GPIOD->MODER |= (1 << 26);	//Setze GPIO 13 auf Output
    GPIOD->MODER |= (1 << 28);	//Setze GPIO 14 auf Output
	GPIOD->MODER |= (1 << 30);	//Setze GPIO 15 auf Output
	
	// Konfiguriere den GPIO-Pin (PD12) für alternative Funktion (AF2)
    GPIOD->AFR[1] |= (2 << 16);  // Set alternative function AF2 for PD12 (Alternative Funktion AF2 für PD12 setzen)

    // Konfiguriere PD12 (LED 4) für den alternativen Push-Pull-Modus
    GPIOD->MODER |= GPIO_MODER_MODE12_1;  // Set alternative function (AF2) for PD12 (Alternative Funktion AF2 für PD12 setzen)
}

/* LED Toggeln mit ODR (Output Data Register)
 * Jedes Bit im ODR-Register repräsentiert einen einzelnen GPIO-Pin. Das Setzen 
 * eines Bits auf 1 setzt den entsprechenden Pin auf HIGH, und das Zurücksetzen 
 * auf 0 setzt den Pin auf LOW.
 */
void drv_led_toggle(uint32_t uiLED) {
    if(11 < uiLED && uiLED < 16) {
        //Zustand des Pins wird umgekehrt
        GPIOD->ODR ^= (1 << uiLED);
    }   
}

/* LED ON/OFF mit BSRR (Bit Set/Reset Register)
 * Mit den unteren 16 Bits des BSRR wird ein Bit gesetzt,
 * mit den oberen 16 Bits wird zurückgesetzt
 */
void drv_led_ON(uint32_t uiLED) {
    if(11 < uiLED && uiLED < 16) {
        //Setzt den zugehörigen Pin auf HIGH
        GPIOD->BSRR |= (1 << uiLED);
    }
}
void drv_led_OFF(uint32_t uiLED) {
    if(11 < uiLED && uiLED < 16) {
        //Setzt den zugehörigen Pin auf LOW
        //+16, da die oberen 16 Bits zum rücksetzen verwendet werden
        GPIOD->BSRR |= (1 << (uiLED + 16));
    }
}