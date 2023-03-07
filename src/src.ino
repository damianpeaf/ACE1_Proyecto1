/*
    Código fuente - Proyecto 1 - Arquitectura de Computadores y Ensambladores 1
    Grupo:  07
    Integrantes:
        - Alvaro Norberto García Meza 202109567
        - Damián Ignacio Peña Afre 202110568
        - Daniel Estuardo Cuque Ruíz 202112145
        - José Manuel Ibarra Pirir 202001800
*/

#include "main.h"
#include "eeprom_manager.h"


void setup() {
    Serial.begin(9600);
    reset_eeprom();
    menu_setup();
}

void loop() {
    menu_loop();
}