# Dokumentation
### Fragen
**Frage 1**

Werden Interrupts mehrfach ausgelöst, während der Interrupt Handler gerade noch bearbeitet wird, soll der Interrupt in einer FIFO-Liste gespeichert werden um als nächstes ausgeführt zu werden.
Vorteile: 
- Interrupts gehen nicht verloren
Nachteile:
- Bearbeitung des Interrupts dauert länger

**Frage 2**

Mit einem Pufferspeicher und jeweils einem Lese/Schreibzugriff.
Wird ein Interrupt ausglöst, wird im Interrupt Handler eine 1 an die aktuelle Stelle im Pufferspeicher geschrieben und die Stelle des Schreibzugriffs um 1 weitergezählt.
In der main-loop wird bei einer 1 an der Stelle des Lesezugriffs eine ISR ausgeführt, danach wird der Lesezugriff um 1 hochgezählt.
Sind Lese- und Schreibzugriff am Ende der Liste angelangt, springen Sie wieder nach vorne.

**Frage 3**

- Probleme: Pufferspeicherüberlauf, ISR kann durch Interrupt unterbrochen werden, Pufferspeicher benötigt Speicher
- Vorteile: Keine Interrupts gehen verloren

**Frage 4**

In dieser Implementation des FiFo-Interrupt Handlers dienen die eigentlichen ISRs nur dazu, einen Bit in die Interrupt-Queue zu setzen, und den pointer für den nächsten Interrupt zu verschieben. In der Main schleife wird schließlich auf gesetzte bits innerhalb der Queue geprüft, und gegebenenfalls die ISR_func Funktion bearbeitet, welche die "eigentliche Funktionalität" der ISR enthält ausgeführt. Der Ablauf wird in der nächsten Frage und dem zugehörigen Diagramm verdeutlicht.

**Frage 5**
```
                       |----|   
ISR_func  -------------|    |------    

                  |--|
ISR       --------|  |-------------

          --------|  |-|    |------
main              |--| |----|
```

