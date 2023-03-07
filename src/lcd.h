#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

void write_bluetooth_logo(LiquidCrystal lcd, int row, int col);

byte bluetoothLogo[8] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11000,
  B10110,
  B00011,
  B00001
};


void write_bluetooth_logo(LiquidCrystal lcd, int row, int col){
  lcd.createChar(0, bluetoothLogo);
  lcd.setCursor(col, row);
  lcd.write(byte(0));
}

void write_price(LiquidCrystal lcd, int price){

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(13, 1);
  lcd.print(".00");

  String price_str = String(price);
  lcd.setCursor(13 - price_str.length(), 1);
  lcd.print(price_str);

  lcd.setCursor(11- price_str.length(), 1);
  lcd.print("Q");

}

#endif