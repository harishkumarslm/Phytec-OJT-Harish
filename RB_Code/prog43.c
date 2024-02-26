#include <TM1637Display.h>

// Define the pins for TM1637 display
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x0a);  // Set the brightness level (0x00 to 0x0f)
}

void loop() {
  for (int i = 0; i <= 9999; i++) {
    display.showNumberDec(i);
    delay(1000);
  }
}

