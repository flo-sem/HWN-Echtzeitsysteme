#include "stm32f4xx.h"
#include "drv_Timer.h"
#include <stddef.h>

void (*func_ptr_CB) (void) = NULL;

void drv_timer4_init(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock
    TIM4->CR1 |= TIM_CR1_CEN;           // Enable Timer 4

    TIM4->PSC = 1600 - 1;  // Set prescaler to 1600 (divide clock by 1600) -> clock 10kHz
    TIM4->ARR = 10 - 1;   // Set auto-reload register to 100
	
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 & ~TIM_CCMR1_OC1M_0; // Set PWM mode 1 (OC1M bits 110)

    TIM4->CCER |= TIM_CCER_CC1E; // Enable Capture/Compare Channel 1

    TIM4->DIER |= TIM_DIER_UIE; // Enable interrupt
	
	NVIC_EnableIRQ(TIM4_IRQn); // NVIC für TIM4 einschalten
    NVIC_SetPriority(TIM4_IRQn, 0); // Priorität von TIM4 auf eins setzen (geringer als EXTI0 -> Button)
}

void drv_timer4_CB_init(void(*callback)(void)) {
	if(callback != NULL)
	{
		func_ptr_CB = callback;
	}
}

void drv_timer4_PWM(uint32_t uiPWM_Start, uint32_t uiPWM_Value) {
	// Set PWM mode 1 (OC1M bits 110)
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; 
    TIM4->CCMR1 &= ~TIM_CCMR1_OC1M_0;

    TIM4->CCER |= TIM_CCER_CC1E; // Enable Capture/Compare Channel 1
	TIM4->CCR1 = uiPWM_Start;
	e_pwm_value = uiPWM_Start;
	e_pwm_increment = uiPWM_Value;
}

void setDutycycle(uint32_t timeIn){
	TIM4->CCR1 = (timeIn/1000);
}

void TIM4_IRQHandler() {
	if (TIM4->SR & TIM_SR_UIF) {
		++now;
		if(func_ptr_CB != NULL)
		{
			func_ptr_CB(); // Execute initalized CB function if it was set.
		}		// Update the PWM value (PWM-Wert aktualisieren)
        TIM4->SR &= ~TIM_SR_UIF; // Clear UIF
    }
}

int getCurrentTime() {
	return now;
}

