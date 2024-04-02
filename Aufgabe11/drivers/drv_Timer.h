#include "stdint.h"

/**
 * @brief Diese Funktion initialisiert den Timer4.
 * 
 * Konfiguration der Register um Timer4 einzuschalten, den Capture/Compare-Kanal einzuschalten, 
 * auf Pwm Mode 1 einzustellen, Prescaler und Auto-Reload-Register zu setzen.
 */
void drv_timer4_init(void);

/**
 * @brief Callback-Funktion für den Underflowflow des Auto-Reload-Registers von Timer4.
 *
 * Diese Funktion ermöglicht die Zuweisung einer Callback-Funktion, die aufgerufen wird,
 * wenn das Auto-Reload-Register von Timer4 Underflowt.
 
 * @param callback Ein Funktionszeiger auf die Callback-Funktion, die bei Tastendruck aufgerufen wird.
 */
void drv_timer4_CB_init(void(*callback)(void));

/**
 * @brief Diese Funktion setzt den PWM-Dutycyle Startwert und den Wert um den er bei jedem Event erhöht wird.
 *
 * Setzen des Startwerts in Capture/Compare Register und setzen des Änderungswerts in globale Variable pwmValue.
 
 * @param uiPWM_Start Startwert für den PWM-Dutcycle.
 * @param uiPWM_Value Wert um den der PWM-Dutycycle bei einem Event geändert wird.
 */
void drv_timer4_PWM(uint32_t uiPWM_Start, uint32_t uiPWM_Value);