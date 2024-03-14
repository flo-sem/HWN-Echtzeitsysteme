#include "drv_Timer.h"
#include <stddef.h>

extern uint16_t pwmValue;

void drv_timer4_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable Timer 4 clock
    TIM4->CR1 |= TIM_CR1_CEN;           // Enable Timer 4

    TIM4->PSC = 1600 - 1;  // Set prescaler to 1600 (divide clock by 1600) -> clock 10kHz
    TIM4->ARR = 100 - 1;   // Set auto-reload register to 100
	
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 & ~TIM_CCMR1_OC1M_0; // Set PWM mode 1 (OC1M bits 110)
    //TIM4->CCMR1 &= ~TIM_CCMR1_OC1M_0;

    TIM4->CCER |= TIM_CCER_CC1E; // Enable Capture/Compare Channel 1
    TIM4->DIER &= ~TIM_DIER_UIE; // Disable update interrupt (Update-Interrupt deaktivieren) ????
}

void drv_timer4_CB_init(void(*callback)(void))
{
	if(!(callback == NULL))
	{
	callback();
	}
}

void drv_timer4_PWM(uint32_t uiPWM_Start, uint32_t uiPWM_Value)
{
	TIM4->CCR1 = uiPWM_Start;
	pwmValue = uiPWM_Value;
} 

