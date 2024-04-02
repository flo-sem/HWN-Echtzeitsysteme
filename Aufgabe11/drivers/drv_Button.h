/**
 * @brief Diese Funktion initialisiert den Button.
 *
 * Neben der Taktversorgung werden auch die Benötigten Register
 * Für die Verwendung des Button-Interrupts gesetzt.
 */
void drv_button_init(void);

/**
 * @brief Callback-Funktion für das Tastendruck-Event.
 *
 * Diese Funktion ermöglicht die Zuweisung einer Callback-Funktion, die aufgerufen wird,
 * wenn der Tastendruck-Event erkannt wird.
 *
 * @param callback Ein Funktionszeiger auf die Callback-Funktion, die bei Tastendruck aufgerufen wird.
 */
void drv_button_CB_pressed_init(void(*)(void));

/**
 * @brief Callback-Funktion für das Tastenfreigabe-Event.
 *
 * Diese Funktion ermöglicht die Zuweisung einer Callback-Funktion, die aufgerufen wird,
 * wenn der Tastenfreigabe-Event erkannt wird.
 *
 * @param callback Ein Funktionszeiger auf die Callback-Funktion, die bei Tastenfreigabe aufgerufen wird.
 */
void drv_button_CB_released_init(void(*)(void));
