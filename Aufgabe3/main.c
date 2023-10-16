//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt f�r Aufgabe 3
// 		Aufgaben:
//		-  User Button �ber Interrupt erkennen
//		-  GPIOD & GPIOA Konfigurieren
//		-  NVIC Konfigurieren
//		-  ISR anlegen
//		-  Interrupt sperren und freigeben
//		-	 Button-Event in statischer Variable speichern
//		-	 LEDs PD13-15 bei gedr�cktem Taster *hoch*,
//			 bei nicht gedr�cktem Taster *runter* z�hlen

int main() {
		RCC->AHB1ENR |= (1<<0);		// Taktversorgung f�r Port A
		RCC->AHB1ENR |= (1<<3);		// Taktversorgung f�r Port D
	
	return 0;
}