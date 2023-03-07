#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include <Key.h>
#include <Keypad.h>

#include "button.h"
#include "lcd.h"
#include "user.h"
#include "user_functions.h"

// ------------------ Menus ------------------ //
const int WELCOME = 0, LOGIN = 1;
int current_menu = WELCOME;

// ------------------ Visualization ------------------ //
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int din = 10, cs = 9, clk = 8;
LedControl matrix(din, cs, clk, 1);

// ------------------ Main Buttons ------------------ //
Button prev_button(22);
Button next_button(25);
Button ok_button(23);
Button cancel_button(24);

// ------------------ Keypad ------------------ //
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7','8','9','C'},
  {'4','5','6','D'},
  {'1','2','3','E'},
  {'A','0','B','F'}
};

byte rowPins[ROWS] = {26, 27, 28, 29};
byte colPins[COLS] = {30, 31, 32, 33};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// ------------------ Functions ------------------ //
void menu_setup();
void menu_loop();

// * Menus
void welcome();
void login();


void menu_setup(){
    lcd.begin(16, 2);
    
    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);

    prev_button.setup();
    next_button.setup();
    ok_button.setup();
    cancel_button.setup();

}

void menu_loop(){
    switch (current_menu)
    {
    case WELCOME:
        welcome();
        break;

    case LOGIN:
        login();
        break;

    default:
        break;
    }
}

void welcome(){
    bool is_bluetooth_connected = false; // ? Global variable
    lcd.clear();

    write_bluetooth_logo(lcd, 0, 0);
    lcd.setCursor(1, 0);
    lcd.print("Bienvenido");
    write_bluetooth_logo(lcd, 0, 11);
    lcd.setCursor(0, 1);
    lcd.print("GRP 07     SEC B");

    while (!is_bluetooth_connected)
    {
        // TODO: Check if bluetooth is connected
        delay(3000);
        is_bluetooth_connected = true;
    }

    while(true){
        if(ok_button.is_pressed()){
            current_menu = LOGIN;
            break;
        }
    }

}

void login(){
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Nickname:");
    String nickname = "";
    while(true){
        char key = keypad.getKey();
        if(key != NO_KEY){
            nickname += key;
            lcd.setCursor(0, 1);
            lcd.print(nickname);
        }
        if(ok_button.is_pressed()){
            break;
        }
    }

    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Password:");
    String password = "";
    while(true){
        char key = keypad.getKey();
        if(key != NO_KEY){
            password += key;
            lcd.setCursor(0, 1);
            lcd.print(password);
        }
        if(ok_button.is_pressed()){
            break;
        }
    }

    User user = login_user(nickname, password);

    if(user.is_valid()){
        String token = get_user_token();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bienvenido");
        lcd.setCursor(0, 1);
        lcd.print(token);
        delay(8000);

        Serial.println(token);
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Credenciales");
        lcd.setCursor(0, 1);
        lcd.print("incorrectas");
        delay(1000);
    }


}


#endif