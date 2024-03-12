/*Externe (globale) Funktionen zum Erkennen von Tastendrücken auf dem Demonoard : */
void drv_button_init(void);
void drv_button_CB_pressed_init(void(*)(void));
void drv_button_CB_released_init(void(*)(void));
