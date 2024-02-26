#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Line 1 data");
  lcd.setCursor(0, 1);
  lcd.print("Line 2 data");
}

void loop() {
  // Your loop code here
}

