//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

//---HEADER---
#include "main.h"
// Projekt für Aufgabe 3
// 		Aufgaben:
//		- 	Effiziente FIFO Struktur implementieren
//		-   Aufgabe 3 von Taster Event auf FIFO umbauen

#define QUEUE_LENGTH = 5
static element queue[5];
static uint32_t last_element;
void delay (int time) {
	for (int i=0; i<10000*time; ++i) {}		
}

void push (uint32_t val){
	for(uint32_t index = 0+last_element;index<5+last_element;++index) {
		int shifted_index = index % 5;
		if(queue[shifted_index].intterrupt_ID == 0) {
			queue[shifted_index].intterrupt_ID = val;
			last_element = shifted_index;
		}	
	}
}

int Element_In_Queue(){
	int sum_of_elements = 0;
	for(int i=0; i<5;i++) {
		sum_of_elements += queue[i].intterrupt_ID;
	}
	return sum_of_elements;
	
}

int Read_and_Remove() {
	int return_var=0;
	for(uint32_t index = 0+last_element+1;index<5+last_element+1;++index) {
		int shifted_index = index % 5;
		if(queue[shifted_index].intterrupt_ID != 0) {
			return_var = queue[shifted_index].intterrupt_ID;
			queue[shifted_index].intterrupt_ID = 0;
			break;
		}	
	}
	return return_var;
}

void Execute_Interrupt_0() {
	GPIOD->BSRR |= (1<<29);		//turn LED off
	delay(20);					//wait for a short period
	GPIOD->BSRR |= (1<<13);		//turn LED back on
}


void EXTI0_IRQHandler() {
	// Auch mölich: NVIC->ICER[0] |= (1<<6);
	if(EXTI->PR & EXTI_PR_PR0) {		// EXTI_PR wird 1 wenn der Interrupt ausgelöst wird
		push(10);
		EXTI->PR |= EXTI_PR_PR0;			// EXTI_PR wird zurückgesetzt, wenn eine 1 reingeschrieben wird
	}
}

void Init_Queue() {
	for(uint32_t i = 0; i<5; ++i) {
		queue[i].next_index	   = 0;
		queue[i].intterrupt_ID = 0;
	}
}


int main() {
	RCC->AHB1ENR |= (1<<0);					// Taktversorgung für Port A
	RCC->AHB1ENR |= (1<<3);					// Taktversorgung für Port D

	GPIOD->MODER |= (1<<26);				//Setze GPIO 13 auf Output

	EXTI->IMR |= (1<<0);						// EXTI0 Maskierung aufheben

	EXTI->RTSR |= (1<<0); 					// EXTI0 auf steigende Flanke setzen
	
	
	NVIC_EnableIRQ(EXTI0_IRQn);			//NVIC für EXTI0 einschalten
	// Oder: NVIC->ISER[0] |= (1<<6);
	
	NVIC_SetPriority(EXTI0_IRQn,0);	// Priorität von EXTI 0 auf null setzen
	// Oder: NVIC->IP[4*6] |= (0<<0);	
	
	
	//---MAIN LOOP---
	while (1) {
		NVIC_EnableIRQ(EXTI0_IRQn);		//NVIC für EXTI0 einschalten
		// Oder: NVIC->ISER[0] |= (1<<6);
		//Logik zum toggeln der LED
		if(Element_In_Queue() > 0 && Read_and_Remove() == 10) {
			Execute_Interrupt_0();
		}
		GPIOD->BSRR |= (1<<13);

	}

}