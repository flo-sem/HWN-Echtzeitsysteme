# Dokumentation
### Fragen
**Frage 1**
Die Default-Interrupt-Handler stehen in der Startup Datei des STM32 Boards.	Sie
sind mit dem Kompiler Schl�sselwort "Weak" vermerkt. Ist ein anderer Handler mit 
dem selben Namen definiert, wird der Default-Handler �berschrieben.
Wollen wir also die ISR selbst definieren, muss die Funktion nur selbstst�ndig
definiert werden:
``` C
void EXTI0_IRQHandler() {
}
```

** Frage 2 **
Die EXTI-Struktur beinhaltet verschiedene Registeraddressen zur bestimmung
des External Interrupt Controllers. F�r uns sind allerdings nur die Register
"IMR" (Interrupt mask register) und "RTSR" (Rising trigger selection register) von
Bedeutung. Wird ein Bit in IMR gesetzt, ist der zugeh�rige EXTI aktiviert.
Mit dem RTSR Register wird die Steigende Flanke als Ausl�ser f�r den Trigger 
angegeben

** Frage 3 **
F�r das freigeben und sperren eines Interrupts exestieren bereits Funktionen:
```C
NVIC_EnableIRQ(EXTI0_IRQn);		//Aktivieren des Interrupts
NVIC_DisableIRQ(EXTI0_IRQn);	//Deaktivieren des Interrupts
```
Diese verwenden Intern ein "Interrupt Set Enable Register" (ISER). Mit diesem
kann unabh�ngig von der Quelle ein Interrupt im NVIC aktiviert und deaktiviert werden.
Da f�r diese L�sung der EXTI0 Interrupt gew�hlt wurde, ist der IRQn_Type 
"EXTI0_IRQn" (=6).

** Frage 4 **

