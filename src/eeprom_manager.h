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

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        product = Product();
        strcpy(product.name, "generic");
        product.price = random(1, 25);
        product.quantity = random(0,100);
        write_product(product);
    }

    // INIT ADMIN USER

    User admin = User();
    admin.isAdmin = true;
    strcpy(admin.name, "ad07min-b");
    strcpy(admin.nickname, "B5155E");
    strcpy(admin.password, "0707B5");
    write_user(admin);


    // Test consumer
    User consumer = User();
    consumer.isAdmin = false;
    strcpy(consumer.name, "damian");
    strcpy(consumer.nickname, "123456");
    strcpy(consumer.password, "123456");
    consumer.credits = 100;
    write_user(consumer);

}

#endif

