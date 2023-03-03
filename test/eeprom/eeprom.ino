//Prueba EEPROM - Proyecto 1 - Arquitectura de Computadores y Ensambladores 1

#include "eeprom_manager.h"

void setup() {
    Serial.begin(9600);
    // reset_eeprom();
}

void loop() {


    User user = get_user(0);
    Serial.println(user.name);
    Serial.println(user.nickname);
    Serial.println(user.password);
    Serial.println(user.credits);
    Serial.println(user.address);
    Serial.println(user.isAdmin);

    Product product = get_product(0);
    Serial.println(product.name);
    Serial.println(product.price);
    Serial.println(product.quantity);
    Serial.println(product.address);

    delay(7000000);

}