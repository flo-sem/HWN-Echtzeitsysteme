/* Include System Libaries */
#include "stm32f4xx.h"

/* Externe (globale) Funktionen zum ansteuern der LEDs auf dem Demoboard: */
/**
 * @brief Initialisiert die Treiberfunktionen für die LED-Steuerung.
 *
 * Diese Funktion initialisiert alle notwendigen Ressourcen für die Steuerung von LEDs.
 * Es werden 4 LEDs 12-15 initialisiert.
 */
void drv_led_init(void);

/**
 * @brief Toggelt den Zustand der angegebenen LED.
 *
 * @param uiLED Die Nummer der LED, deren Zustand getoggelt werden soll.             
 */
void drv_led_toggle(uint32_t uiLED);

/**
 * @brief Schaltet die angegebene LED ein.
 *
 * @param uiLED Die Nummer der LED, die eingeschaltet werden soll.
 */
void drv_led_ON(uint32_t uiLED);

/**
 * @brief Schaltet die angegebene LED aus.
 *
 * @param uiLED Die Nummer der LED, die ausgeschaltet werden soll.
 */
void drv_led_OFF(uint32_t uiLED);