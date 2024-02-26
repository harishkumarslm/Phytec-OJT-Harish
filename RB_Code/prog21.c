#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char line1[] = "Scrolling Text 1";
char line2[] = "Line 2 Data";

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
}

