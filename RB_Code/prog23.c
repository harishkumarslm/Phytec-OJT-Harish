#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte alpha[8] = {B01110, B10001, B10001, B11111, B10001, B10001, B10001, B10001};
byte beta[8] = {B11110, B10001, B10001, B11110, B10001, B10001, B11110, B10000};
byte pie[8] = {B00100, B01010, B01010, B01010, B01010, B10001, B10001, B01110};
byte ohm[8] = {B01110, B10001, B10001, B01110, B00100, B01010, B10001, B01110};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, alpha);
  lcd.createChar(1, beta);
  lcd.createChar(2, pie);
  lcd.createChar(3, ohm);

  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
}

void loop() {
  // Your loop code here
}

