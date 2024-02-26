#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char inputText[16];

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter text:");
  lcd.setCursor(0, 1);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar != '\n') {
      Serial.print(incomingChar);
      strcat(inputText, &incomingChar);
    } else {
      lcd.clear();
      lcd.print("You entered:");
      lcd.setCursor(0, 1);
      lcd.print(inputText);
    }
  }
}

