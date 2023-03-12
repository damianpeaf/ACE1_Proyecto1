#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include <Key.h>
#include <Keypad.h>

#include "button.h"
#include "lcd.h"
#include "matrix.h"

#include "user.h"
#include "product.h"
#include "eeprom_manager.h"
#include "user_functions.h"
#include "custom_stepper.h"

// ------------------ Menus ------------------ //
const int WELCOME = 0, LOGIN = 1, CONSUMER = 2, ADMIN = 3;
const int CONSUMER_MAIN_DASHBOARD = 0, CONSUMER_BUY_PRODUCTS = 1, CONSUMER_CREDITS = 2;
const int ADMIN_MAIN_DASHBOARD = 0, ADMIN_PRODUCT_ACTIONS = 1, ADMIN_REGISTER_USER = 2, ADMIN_STATE = 3;
int current_menu = WELCOME;

// ------------------ Visualization ------------------ //
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int din = 10, cs = 9, clk = 8;
LedControl matrix(din, clk, cs, 1);

// ------------------ Main Buttons ------------------ //
Button prev_button(22);
Button next_button(25);
Button ok_button(23);
Button cancel_button(24);

// ------------------ Keypad ------------------ //
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'7', '8', '9', 'C'},
    {'4', '5', '6', 'D'},
    {'1', '2', '3', 'E'},
    {'A', '0', 'B', 'F'}};

byte rowPins[ROWS] = {26, 27, 28, 29};
byte colPins[COLS] = {30, 31, 32, 33};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

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
void sale_details(Product product);
void consumer_credits(int *current_menu);

// * Admin
void admin_dashboard();
void admin_main_dashboard(int *current_menu, bool *session);
void admin_add_user(int *current_menu);
void admin_product_actions(int *current_menu);
void admin_register_user(int *current_menu);
void modify_product(Product product);

void menu_setup()
{
    lcd.begin(16, 2);

    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);

    prev_button.setup();
    next_button.setup();
    ok_button.setup();
    cancel_button.setup();
}

void menu_loop()
{
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
        admin_dashboard();
        break;
        // TODO:
        break;

    default:
        break;
    }
}

void welcome()
{
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

        is_bluetooth_connected = true; // ! TEST PURPOSES ONLY

        while (Serial1.available())
        {
            delay(10);
            char c = Serial1.read();
            text += c;
        }

        if (text.length() > 0 && text == "connected")
        {
            is_bluetooth_connected = true;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bluetooth");
            lcd.setCursor(0, 1);
            lcd.print("Connected");
            text = "";
            delay(1000);
        }
    }

    write_bluetooth_logo(lcd, 0, 0);
    lcd.setCursor(1, 0);
    lcd.print("Bienvenido");
    write_bluetooth_logo(lcd, 0, 11);
    lcd.setCursor(0, 1);
    lcd.print("GRP 07     SEC B");

    while (true)
    {
        if (ok_button.is_pressed())
        {
            current_menu = LOGIN;
            break;
        }
    }
}

void login()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Nickname:");
    String nickname = "";
    while (true)
    {
        char key = keypad.getKey();
        if (key != NO_KEY)
        {

            if(nickname.length()<10){
                nickname += key;
                lcd.setCursor(0, 1);
                lcd.print(nickname);
            }else{
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print("MAX");
                delay(1000);
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print(nickname);
            }
        }
        if (ok_button.is_pressed())
        {
            break;
        }

        if (cancel_button.is_pressed())
        {
            if (nickname.length() > 0)
            {
                nickname.remove(nickname.length() - 1);
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print(nickname);
            }
        }
    }

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Password:");
    String password = "";
    while (true)
    {
        char key = keypad.getKey();
        if (key != NO_KEY)
        {
            if(password.length()<10){
                password += key;
                lcd.setCursor(0, 1);
                lcd.print(password);
            }else{
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print("MAX");
                delay(1000);
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print(password);
            }
        }
        if (ok_button.is_pressed())
        {
            break;
        }

        if (cancel_button.is_pressed())
        {
            if (password.length() > 0)
            {
                password.remove(password.length() - 1);
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print(password);
            }
        }
    }

    User user = login_user(nickname, password);

    if (user.is_valid())
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Generating");
        lcd.setCursor(0, 1);
        lcd.print("token");

        String token = get_user_token();
        Serial1.write("token");
        delay(3000);
        Serial1.write(token.c_str());
        delay(1000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Token:");

        int tries = 0;
        bool is_token_validated = false;
        String token_received = "";

        while (!is_token_validated)
        {

            is_token_validated = true; // ! TEST PURPOSES ONLY

            char key = keypad.getKey();
            if (key != NO_KEY)
            {
                token_received += key;
                lcd.setCursor(0, 1);
                lcd.print(token_received);
            }

            if (ok_button.is_pressed())
            {
                if (token_received == token)
                {
                    is_token_validated = true;
                    break;
                }
                else
                {
                    tries++;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Invalid token");
                    lcd.setCursor(0, 1);
                    lcd.print("Tries: " + String(tries));
                    delay(1000);
                    token_received = "";
                    lcd.clear();
                }
            }

            if (tries >= 3)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("No more tries");
                delay(10000);
                break;
            }
        }

        if (is_token_validated)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Welcome");
            lcd.setCursor(0, 1);
            lcd.print(user.nickname);

            authenticated_user = user;

            if (user.isAdmin)
            {
                Serial1.write("admin");
                current_menu = ADMIN;
            }
            else
            {
                Serial1.write("consumer");
                current_menu = CONSUMER;
            }

            delay(1000);
        }
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incorrect");
        lcd.setCursor(0, 1);
        lcd.print("Credentials");
        delay(1000);
    }
}

// -------------------------------------- CONSUMER --------------------------------------

void consumer_dashboard()
{

    lcd.clear();

    bool session = true;
    int current_menu = CONSUMER_MAIN_DASHBOARD;

    int *current_menu_ptr = &current_menu;
    bool *session_ptr = &session;

    while (session)
    {
        switch (current_menu)
        {
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

void consumer_main_dashboard(int *current_consumer_menu, bool *session)
{
    lcd.clear();
    bool end = false;
    int current_option = 0;

    while (!end)
    {
        lcd.setCursor(0, 0);

        switch (current_option)
        {
        case 0:
            lcd.print("Buy products");
            break;
        case 1:
            lcd.print("Credits");
            break;
        case 2:
            lcd.print("Logout");
            break;
        }

        lcd.setCursor(0, 1);
        lcd.print("<-            ->");

        if (next_button.is_pressed())
        {
            current_option++;
            if (current_option > 2)
            {
                current_option = 0;
            }
            lcd.clear();
        }

        if (prev_button.is_pressed())
        {
            current_option--;
            if (current_option < 0)
            {
                current_option = 2;
            }
            lcd.clear();
        }

        if (ok_button.is_pressed())
        {
            switch (current_option)
            {
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
                Serial1.write("logout");
                break;
            }
        }
    }
}

void consumer_buy_products(int *current_menu)
{

    lcd.clear();
    int current_product_index = 0;
    bool exit = false;

    Product current_product = get_product(current_product_index);

    while (!exit)
    {

        lcd.setCursor(0, 0);
        lcd.print(String(current_product.name));
        lcd.setCursor(0, 1);
        write_price(lcd, current_product.price);
        matrix_print_number(matrix, current_product.quantity);

        while (true)
        {

            // TODO: MOVE STEPPER, 36° each product

            if (next_button.is_pressed())
            {
                current_product_index++;
                if (current_product_index >= get_product_count())
                {
                    current_product_index = 0;
                }
                lcd.clear();
                current_product = get_product(current_product_index);
                break;
            }

            if (prev_button.is_pressed())
            {
                current_product_index--;
                if (current_product_index < 0)
                {
                    current_product_index = get_product_count();
                }
                lcd.clear();
                current_product = get_product(current_product_index);
                break;
            }

            if (ok_button.is_pressed())
            {
                sale_details(current_product);
                // Update product reference
                current_product = get_product(current_product_index);
                break;
            }

            if (cancel_button.is_pressed())
            {
                exit = true;
                break;
            }
        }
    }

    *current_menu = CONSUMER_MAIN_DASHBOARD;
}

void sale_details(Product product)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Quantity: ");

    String required_quantity_str = "";
    String error_message = "";
    while (true)
    {

        char key = keypad.getKey();

        if (key != NO_KEY && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != 'E' && key != 'F')
        {
            required_quantity_str += key;
            lcd.setCursor(10, 1);
            lcd.print(required_quantity_str);
        }

        if (cancel_button.is_pressed())
        {
            break;
        }

        if (ok_button.is_pressed())
        {
            // * Check for available quantity
            int required_quantity = required_quantity_str.toInt();

            if (required_quantity > product.quantity)
            {
                error_message = "Not enough quantity";
            }
            else if (required_quantity * product.price > authenticated_user.credits)
            {
                error_message = "Not enough credits";
            }
            else
            {
                authenticated_user.credits -= required_quantity * product.price;
                product.quantity -= required_quantity;

                // * Update product quantity and user credits
                update_product(product);
                update_user(authenticated_user);

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Sale completed");
                lcd.setCursor(0, 1);
                lcd.print("Dispatching...");
                Serial1.write("compra realizada");
                delay(2000); // ! REMOVE THIS
                lcd.clear();

                // TODO: MOVE SERVO
            }

            break;
        }
    }

    if (error_message != "")
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(error_message);
        // TODO: Send error message to app
        Serial1.write(error_message.c_str());
        delay(2000);
        lcd.clear();
    }
}

void consumer_credits(int *current_menu)
{

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Credits: " + String(authenticated_user.credits));
    lcd.setCursor(0, 1);
    lcd.print("OK: back");

    while (true)
    {
        if (ok_button.is_pressed())
        {
            break;
        }
    }
    *current_menu = CONSUMER_MAIN_DASHBOARD;
}

// -------------------------------------- ADMIN --------------------------------------

void admin_dashboard()
{
    lcd.clear();

    bool session = true;
    int current_menu = CONSUMER_MAIN_DASHBOARD;

    int *current_menu_ptr = &current_menu;
    bool *session_ptr = &session;

    while (session)
    {
        switch (current_menu)
        {
        case ADMIN_MAIN_DASHBOARD:
            admin_main_dashboard(current_menu_ptr, session_ptr);
            break;
        case ADMIN_PRODUCT_ACTIONS:
            admin_product_actions(current_menu_ptr);
            break;
        case ADMIN_REGISTER_USER:
            admin_register_user(current_menu_ptr);
            break;
        case ADMIN_STATE:
            // TODO
            break;
        }
    }
}

void admin_main_dashboard(int *current_admin_menu, bool *session)
{
    lcd.clear();
    bool end = false;
    int current_option = 0;

    while (!end)
    {
        lcd.setCursor(0, 0);

        switch (current_option)
        {
        case 0:
            lcd.print("Productos");
            break;
        case 1:
            lcd.print("Registrar user");
            break;
        case 2:
            lcd.print("Ver estado");
            break;
        case 3:
            lcd.print("Cerrar sesion");
            break;
        }

        lcd.setCursor(0, 1);
        lcd.print("<-            ->");

        if(next_button.is_pressed()){
            current_option++;
            if (current_option > 3)
            {
                current_option = 0;
            }
            lcd.clear();
        }

        if (prev_button.is_pressed())
        {
            current_option--;
            if (current_option < 0)
            {
                current_option = 3;
            }
            lcd.clear();
        }

        if (ok_button.is_pressed())
        {
            switch (current_option)
            {
            case 0:
                *current_admin_menu = ADMIN_PRODUCT_ACTIONS;
                end = true;
                break;
            case 1:
                end = true;
                *current_admin_menu = ADMIN_REGISTER_USER;
                break;
            case 2:
                end = true;
                *current_admin_menu = ADMIN_STATE;
                break;
            case 3:
                end = true;
                *session = false;
                current_menu = WELCOME;
                break;
            }
        }
    }
}

void admin_product_actions(int *current_menu){

    lcd.clear();
    int current_product_index = 0;
    bool exit = false;

    Product current_product = get_product(current_product_index);

    while(!exit){

        lcd.setCursor(0, 0);
        lcd.print(String(current_product.name));
        lcd.setCursor(0, 1);
        write_price(lcd, current_product.price);
        matrix_print_number(matrix, current_product.quantity);

        while(true){
            if(next_button.is_pressed()){
                current_product_index++;
                if(current_product_index >= get_product_count()){
                    current_product_index = 0;
                }
                lcd.clear();
                current_product = get_product(current_product_index);
                break;
            }

            if(prev_button.is_pressed()){
                current_product_index--;
                if(current_product_index < 0){
                    current_product_index = get_product_count();
                }
                lcd.clear();
                current_product = get_product(current_product_index);
                break;
            }

            if(ok_button.is_pressed() && current_product.quantity == 0){
                modify_product(current_product);
                current_product = get_product(current_product_index);
                break;
            }
                

            if(cancel_button.is_pressed()){
                exit = true;
                break;
            }
        }

    }

    *current_menu = ADMIN_MAIN_DASHBOARD;
}

void modify_product(Product product){
    lcd.clear();
    bool end = false;
    int current_option = 0;
    
    while(!end){

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Nombre:");
        String nombre = "";
        while (Serial1.available())
        {
            delay(10);
            char c = Serial1.read();
            nombre += c;
        }
        Serial1.write("name");
        /*while(true){
            char key = keypad.getKey();
            if(key != NO_KEY){
                nombre += key;
                lcd.setCursor(0, 1);
                lcd.print(nombre);
            }
            if(ok_button.is_pressed()){
                break;
            }
        }*/

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Cantidad:");
        String cantidad = "";
        while(true){
            char key = keypad.getKey();
            if(key != NO_KEY){
                cantidad += key;
                lcd.setCursor(0, 1);
                lcd.print(cantidad);
            }
            if(ok_button.is_pressed()){
                break;
            }
        }

        lcd.clear();
    
        lcd.setCursor(0, 0);
        lcd.print("Precio:");
        String precio = "";
        while(true){
            char key = keypad.getKey();
            if(key != NO_KEY){
                precio += key;
                lcd.setCursor(0, 1);
                lcd.print(precio);
            }
            if(ok_button.is_pressed()){
                lcd.clear();
                
                if(nombre.length() > 0 && nombre.length() <=16 && cantidad.toInt() > 0 && cantidad.toInt() < 100) {
                    strcpy(product.name, nombre.c_str());
                    product.quantity = cantidad.toInt();
                    product.price = precio.toInt();
                    update_product(product);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Modified");
                    delay(1000);
                    end = true;
                    break;
                }else{
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Error");
                    Serial1.write("error");
                    delay(1000);
                    end = true;
                    break;
                }
            
                
            }
        }
        
    }
}

void admin_register_user(int *current_menu){

    lcd.clear();
    bool end = false;
    int current_option = 0;
    
    while(!end){

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Nombre:");
        String nombre = "";
        while (Serial1.available())
        {
            delay(10);
            char c = Serial1.read();
            nombre += c;
        }
        Serial1.write("name");
        /*while(true){
            char key = keypad.getKey();
            if(key != NO_KEY){
                nombre += key;
                lcd.setCursor(0, 1);
                lcd.print(nombre);
            }
            if(ok_button.is_pressed()){
                break;
            }
        }*/

        lcd.clear();
    
        lcd.setCursor(0, 0);
        lcd.print("Apodo:");
        String apodo = "";
        while(true){
            char key = keypad.getKey();
            if(key != NO_KEY){
                apodo += key;
                lcd.setCursor(0, 1);
                lcd.print(apodo);
            }
            if(ok_button.is_pressed()){
                break;
            }
        }

        lcd.clear();
    
        lcd.setCursor(0, 0);
        lcd.print("Contraseña:");
        String password = "";
        while(true){
            char key = keypad.getKey();
            if(key != NO_KEY){
                password += key;
                lcd.setCursor(0, 1);
                lcd.print(password);
            }
            if(ok_button.is_pressed()){
                lcd.clear();
                User consumer = User();
                if(is_user_registered(apodo.c_str())){
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("User exists");
                    Serial1.write("error");
                    delay(1000);
                }else{
                    consumer.isAdmin = false;
                    strcpy(consumer.name, nombre.c_str());
                    strcpy(consumer.nickname, apodo.c_str());
                    strcpy(consumer.password, password.c_str());
                    consumer.credits = 250;
                    Serial.print("Registrado ");
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("User registered");
                    delay(1000);
                    write_user(consumer);
                }
                *current_menu = ADMIN_MAIN_DASHBOARD;
                end = true;
                break;
            }
        }
    }
}


void admin_state(int *current_menu){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ver estado");
    delay(2000);
    *current_menu = CONSUMER_MAIN_DASHBOARD;
}

#endif