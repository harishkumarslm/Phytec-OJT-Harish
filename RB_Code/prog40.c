#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the I2C address for the LCD

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  lcd.backlight();   // Turn on the backlight
  lcd.print("Hello, World!");
}

void loop() {
  // Your code here to update and display data on the LCD
}

