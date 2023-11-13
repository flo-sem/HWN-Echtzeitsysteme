# Dokumentation
### Fragen
**Frage 1**

**Frage 2**

**Frage 3**


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

