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
const int WELCOME = 0, LOGIN = 1, CONSUMER = 2, ADMIN = 3;
const int CONSUMER_MAIN_DASHBOARD = 0, CONSUMER_BUY_PRODUCTS = 1, CONSUMER_CREDITS = 2;

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

// ------------------ User ------------------ //
User authenticated_user;

// ------------------ Functions ------------------ //
void menu_setup();
void menu_loop();

// * Menus
void welcome();
void login();

// * Consumer
void consumer_dashboard();
void consumer_main_dashboard(int *current_menu, bool *session);
void consumer_buy_products(int *current_menu);
void consumer_credits(int *current_menu);

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
    
    case CONSUMER:
        consumer_dashboard();
        break;

    case ADMIN:
        // TODO: 
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

    String text = "";
    while (!is_bluetooth_connected)
    {
         while(Serial1.available()){
            delay(10);
            char c = Serial1.read();
            text += c;
        }

        if(text.length() > 0 && text == "connected"){
            is_bluetooth_connected = true;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Bluetooth connected");
            text="";
            delay(1000);
        }
    }

    write_bluetooth_logo(lcd, 0, 0);
    lcd.setCursor(1, 0);
    lcd.print("Bienvenido");
    write_bluetooth_logo(lcd, 0, 11);
    lcd.setCursor(0, 1);
    lcd.print("GRP 07     SEC B");

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

        Serial1.write(token.c_str());

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingresa el token:");

        int tries = 0;
        bool is_token_validated = false;
        String token_received = "";

        while(!is_token_validated){
            
            char key = keypad.getKey();
            if(key != NO_KEY){
                token_received += key;
                lcd.setCursor(0, 1);
                lcd.print(token_received);
            }

            if(ok_button.is_pressed()){
                if(token_received == token){
                    is_token_validated = true;
                    break;
                } else {
                    tries++;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Token invalido");
                    lcd.setCursor(0, 1);
                    lcd.print("Intentos: " + String(tries));
                    delay(1000);
                    token_received = "";
                }
            }

            if(tries >= 3){
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Intentos agotados");
                delay(10000);
                break;
            }
        }


        if(is_token_validated){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bienvenido");
            lcd.setCursor(0, 1);
            lcd.print(user.nickname);

            authenticated_user = user;
            
            if(user.isAdmin){
                current_menu = ADMIN;
            } else {
                current_menu = CONSUMER;
            }

            delay(1000);
        }


    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Credenciales");
        lcd.setCursor(0, 1);
        lcd.print("incorrectas");
        delay(1000);
    }
}

void consumer_dashboard(){

    lcd.clear();

    bool session = true;
    int current_menu = CONSUMER_MAIN_DASHBOARD;
    
    int *current_menu_ptr = &current_menu;
    bool *session_ptr = &session;

    while(session){
        switch (current_menu){
            case CONSUMER_MAIN_DASHBOARD:
                consumer_main_dashboard(current_menu_ptr, session_ptr);
                break;  
            case CONSUMER_BUY_PRODUCTS:
                consumer_buy_products(current_menu_ptr);
                break;
            case CONSUMER_CREDITS:
                consumer_credits(current_menu_ptr);
                break;
        }
    }
}

void consumer_main_dashboard(int *current_consumer_menu, bool *session){
    lcd.clear();
    bool end = false;
    int current_option = 0;
    
    while(!end){
        lcd.setCursor(0, 0);
            
        switch (current_option){
            case 0:
                lcd.print("Comprar Productos");
                break;
            case 1:
                lcd.print("Ver creditos");
                break;
            case 2:
                lcd.print("Cerrar sesion");
                break;
        }

        if(next_button.is_pressed()){
            current_option++;
            if(current_option > 2){
                current_option = 0;
            }
            lcd.clear();
        }

        if(prev_button.is_pressed()){
            current_option--;
            if(current_option < 0){
                current_option = 2;
            }
            lcd.clear();
        }

        if(ok_button.is_pressed()){
            switch (current_option){
                case 0:
                    *current_consumer_menu = CONSUMER_BUY_PRODUCTS;
                    end = true;
                    break;
                case 1:
                    end = true;
                    *current_consumer_menu = CONSUMER_CREDITS;
                    break;
                case 2:
                    end = true;
                    *session = false;
                    current_menu = WELCOME;
                    break;
            }
        }
    }
}

void consumer_buy_products(int *current_menu){
    // TODO:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Comprar productos");
    delay(2000);
    *current_menu = CONSUMER_MAIN_DASHBOARD;
}

void consumer_credits(int *current_menu){

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ver creditos");
    lcd.setCursor(0, 1);
    lcd.print(String(authenticated_user.credits));

    while(true){
        if(ok_button.is_pressed()){
            break;
        }
    }
    *current_menu = CONSUMER_MAIN_DASHBOARD;
}

#endif