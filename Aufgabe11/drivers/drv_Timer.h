/* Include System Libaries */
#include "stm32f4xx.h"

/*Externe (globale) Funktionen zur Meldung eines periodischen Taktsignals und der Augabe eines PWM-Signals: */
void drv_timer4_init(void);
void drv_timer4_CB_init(void(*)(void));
void drv_timer4_PWM(uint32_t uiPWM_Start, uint32_t uiPWM_Value);