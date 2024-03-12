/* Include System Libaries */
#include "stm32f4xx.h"



/*Externe (globale) Funktionen zur Meldung eines periodischen Taktsignals und der Augabe eines PWM-Signals: */
/**
 * @brief initialize timer4.
 * @return void.
 */
void drv_timer4_init(void);

/**
 * @brief initialize timer 4.
 * @return void.
 */
void drv_timer4_CB_init(void(*callback)(void));
void drv_timer4_PWM(uint32_t uiPWM_Start, uint32_t uiPWM_Value);