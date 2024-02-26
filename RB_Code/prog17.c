#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello, 8-bit!");
}

void loop() {
  // Your loop code here
}

