#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char message[] = "Scrolling Text ";

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(message);
    delay(500);
  }
}

