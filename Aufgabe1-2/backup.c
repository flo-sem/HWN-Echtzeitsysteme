
//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"



//---FUNCTIONS---
static void SetSystemClockTo16Mhz(void)
{
  /* Enabling the HSI clock - If not enabled and ready */
  if( (RCC->CR & RCC_CR_HSIRDY) == 0) 
  {
    RCC->CR |= RCC_CR_HSION;  /* HSION=1 */
  
    /* Waiting until HSI clock is ready */
    while( (RCC->CR & RCC_CR_HSIRDY) == 0);
  }
  
  /* Select AHB prescaler to 1 */
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
  
  /* APB1 prescaler to 1 */
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;
  
  /* APB2 prescaler to 1 */
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
  
  /* Select the HSI as system clock source */
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= RCC_CFGR_SW_HSI;
  
  /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
  FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;
  
  /* Disabling HSE Clock*/
  RCC->CR &= ~RCC_CR_HSEON;
}


void SysTickHandler(void){
	GPIOD->BSRR |= (1<<13);
}

void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF) {
		TIM2->SR &= ~TIM_SR_UIF;
		
		SysTickHandler();
	}
}
	
int main() {
	RCC->AHB1ENR |= (1<<0);		// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);		// Taktversorgung für Port D

	//GPIO->Moder... nicht benötigt, da Input Port
	GPIOD->MODER |= (1<<24);	//Setze GPIO 12 auf Output
	GPIOD->MODER |= (1<<26);	//Setze GPIO 13 auf Output
	
	SetSystemClockTo16Mhz();
	//---INTERRUPT CONFIG---
	RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;	//Starte Clock für TIM2	
	
	TIM2->PSC = 15;							//Einstellungen für prescaler
	TIM2->ARR = 999;     					//10000 Cyklen pro Sekunde
	TIM2->DIER |= TIM_DIER_UIE;				//Aktiviere Timer Interrupt
	TIM2->CR1 = 1; //|= TIM_CR1_CEN;				//Aktiviere Timer
	NVIC_EnableIRQ(TIM2_IRQn); 				//Startet Timer2 im NVIC
	NVIC_SetPriority(TIM2_IRQn, 0);			//Priorität für TIM2
	
	__enable_irq();

	
	//---MAIN LOOP---
	while (1) {
		if(GPIOA->IDR & (1<<0))  //Button is Pressed
		{
			GPIOD->BSRR |= (1<<12);
			GPIOD->BSRR |= (1<<13);

		}
		else 
		{
			GPIOD->BSRR |= (1<<28);
			GPIOD->BSRR |= (1<<29);
		}

	}	
}

