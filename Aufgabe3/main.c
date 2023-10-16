//---INCLUDES---
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

// Projekt für Aufgabe 3
// 		Aufgaben:
//		-  User Button über Interrupt erkennen
//		-  GPIOD & GPIOA Konfigurieren
//		-  NVIC Konfigurieren
//		-  ISR anlegen
//		-  Interrupt sperren und freigeben
//		-	 Button-Event in statischer Variable speichern
//		-	 LEDs PD13-15 bei gedrücktem Taster *hoch*,
//			 bei nicht gedrücktem Taster *runter* zählen

int main() {
		RCC->AHB1ENR |= (1<<0);		// Taktversorgung für Port A
		RCC->AHB1ENR |= (1<<3);		// Taktversorgung für Port D
	
	return 0;
}