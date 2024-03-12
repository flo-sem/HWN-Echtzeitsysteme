/* Include System Libaries */
#include "stm32f4xx.h"

/* Externe (globale) Funktionen zum ansteuern der LEDs auf dem Demoboard: */
void drv_led_init(void);
void drv_led_toggle(uint32_t uiLED);
void drv_led_ON(uint32_t uiLED);
void drv_led_OFF(uint32_t uiLED);