#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

#include "user.h"
#include "product.h"

const int MAX_MEMORY = 4095;

const int PRODUCT_COUNT_ADDRESS = 0;
const int CURRENT_PRODUCT_ADDRESS = 1 * sizeof(int);
const int PRODUCTS_BLOCK_START_ADDRESS = 2 * sizeof(int);
const int MAX_PRODUCTS = 10;

const int USER_COUNT_ADDRESS = MAX_PRODUCTS * sizeof(Product) + PRODUCTS_BLOCK_START_ADDRESS;
const int CURRENT_USER_ADDRESS = 1 * sizeof(int) + USER_COUNT_ADDRESS;
const int USERS_BLOCK_START_ADDRESS = 2 * sizeof(int) + USER_COUNT_ADDRESS;

// ----------------- FUNCTIONS -----------------

int get_product_count();
void set_product_count(int count);
int get_current_product_address();
void write_product(Product product);
Product get_product(int index);
void update_product(Product product);

int get_user_count();
void set_user_count(int count);
int get_current_user_address();
void write_user(User user);
User get_user(int index);
void update_user(User user);



// ----------------- PRODUCTS -----------------

int get_product_count() {
    int count;
    EEPROM.get(PRODUCT_COUNT_ADDRESS, count);
    return count;
}

void set_product_count(int count) {
    EEPROM.put(PRODUCT_COUNT_ADDRESS, count);
}

int get_current_product_address() {
    int address;
    EEPROM.get(CURRENT_PRODUCT_ADDRESS, address);
    return address;
}

void write_product(Product product) {

    int product_count = get_product_count();

    if (product_count >= MAX_PRODUCTS) {
        Serial.println("Max products reached");
        return;
    }

    set_product_count(product_count + 1);
    product.address = get_current_product_address();
    EEPROM.put(get_current_product_address(), product);
    EEPROM.put(CURRENT_PRODUCT_ADDRESS, product.address + sizeof(Product));
}

Product get_product(int index) {

    Product product;
    if(index < 0 || index >= get_product_count()) {
        Serial.println("Invalid product index");
        product = Product();
        return product;
    }

    int address = PRODUCTS_BLOCK_START_ADDRESS + (index * sizeof(Product));
    EEPROM.get(address, product);
    return product;
}

void update_product(Product product) {
    EEPROM.put(product.address, product);
}

// ----------------- USERS -----------------

int get_user_count() {
    int count;
    EEPROM.get(USER_COUNT_ADDRESS, count);
    return count;
}

void set_user_count(int count) {
    EEPROM.put(USER_COUNT_ADDRESS, count);
}

int get_current_user_address() {
    int address;
    EEPROM.get(CURRENT_USER_ADDRESS, address);
    return address;
}

void write_user(User user) {

    if(get_current_user_address() >= MAX_MEMORY) {
        Serial.println("Max memory reached");
        return;
    }

    int user_count = get_user_count();
    
    set_user_count(user_count + 1);
    user.address = get_current_user_address();
    EEPROM.put(get_current_user_address(), user);
    EEPROM.put(CURRENT_USER_ADDRESS, user.address + sizeof(User));
}

User get_user(int index) {

    User user;
    if(index < 0 || index >= get_user_count()) {
        Serial.println("Invalid user index");
        user = User();
        return user;
    }

    int address = USERS_BLOCK_START_ADDRESS + (index * sizeof(User));
    EEPROM.get(address, user);
    return user;
}

void update_user(User user) {
    EEPROM.put(user.address, user);
}


// ------------------------------

void reset_eeprom() {

    EEPROM.put(PRODUCT_COUNT_ADDRESS, 0);
    EEPROM.put(CURRENT_PRODUCT_ADDRESS, PRODUCTS_BLOCK_START_ADDRESS);

    EEPROM.put(USER_COUNT_ADDRESS, 0);
    EEPROM.put(CURRENT_USER_ADDRESS, USERS_BLOCK_START_ADDRESS);

    Serial.println("EEPROM reseted");

    // INIT PRODUCTS

    Product product;
        
    product = Product(); // * 1
    strcpy(product.name, "Doritos");
    product.price = 5;
    product.quantity = 5;
    write_product(product);

    product = Product(); // * 2
    strcpy(product.name, "Coca Cola");
    product.price = 4;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 3
    strcpy(product.name, "Pepsi");
    product.price = 4;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 4
    strcpy(product.name, "Fanta");
    product.price = 4;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 5
    strcpy(product.name, "Sprite");
    product.price = 4;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 6
    strcpy(product.name, "Tortrix");
    product.price = 3;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 7
    strcpy(product.name, "Cheetos");
    product.price = 3;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 8
    strcpy(product.name, "Lays");
    product.price = 3;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 9
    strcpy(product.name, "Takis");
    product.price = 3;
    product.quantity = 10;
    write_product(product);

    product = Product(); // * 10
    strcpy(product.name, "Grapete");
    product.price = 3;
    product.quantity = 10;
    write_product(product);


    // INIT ADMIN USER

    User admin = User();
    admin.isAdmin = true;
    strcpy(admin.name, "ad07min-b");
    strcpy(admin.nickname, "B5155E");
    strcpy(admin.password, "0707B5");
    write_user(admin);


    // Test consumers

    User consumer;
    
    consumer = User();
    consumer.isAdmin = false;
    strcpy(consumer.name, "damian");
    strcpy(consumer.nickname, "123456");
    strcpy(consumer.password, "123456");
    consumer.credits = 100;
    write_user(consumer);

    consumer = User();
    consumer.isAdmin = false;
    strcpy(consumer.name, "alvaro");
    strcpy(consumer.nickname, "111111");
    strcpy(consumer.password, "111111");
    consumer.credits = 50;
    write_user(consumer);

    consumer = User();
    consumer.isAdmin = false;
    strcpy(consumer.name, "jose");
    strcpy(consumer.nickname, "222222");
    strcpy(consumer.password, "222222");
    consumer.credits = 20;
    write_user(consumer);

    consumer = User();
    consumer.isAdmin = false;
    strcpy(consumer.name, "daniel");
    strcpy(consumer.nickname, "333333");
    strcpy(consumer.password, "333333");
    consumer.credits = 10;
    write_user(consumer);

}

#endif

