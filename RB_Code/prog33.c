#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define POT_PIN 0 // Replace with the actual GPIO pin number

int main() {
    wiringPiSetup();

    pinMode(POT_PIN, INPUT);

    while (1) {
        int potValue = analogRead(POT_PIN);
        printf("Analog Value from POT: %d\n", potValue);
        delay(1000); // Delay 1 second
    }

    return 0;
}

